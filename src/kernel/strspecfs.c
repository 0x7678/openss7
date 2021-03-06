/*****************************************************************************

 @(#) $RCSfile: strspecfs.c,v $ $Name:  $($Revision: 1.1.2.11 $) $Date: 2011-09-20 09:51:39 $

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2013  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation, version 3 of the license.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
 details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>, or
 write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA.

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 -----------------------------------------------------------------------------

 Last Modified $Date: 2011-09-20 09:51:39 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: strspecfs.c,v $
 Revision 1.1.2.11  2011-09-20 09:51:39  brian
 - updates from git

 Revision 1.1.2.10  2011-09-02 08:46:51  brian
 - sync up lots of repo and build changes from git

 Revision 1.1.2.9  2011-05-31 09:46:09  brian
 - new distros

 Revision 1.1.2.8  2011-04-07 15:24:04  brian
 - weak reference corrections

 Revision 1.1.2.7  2011-04-05 16:35:14  brian
 - weak module design

 Revision 1.1.2.6  2011-03-26 04:28:48  brian
 - updates to build process

 Revision 1.1.2.5  2011-01-13 16:19:08  brian
 - changes for SLES 11 support

 Revision 1.1.2.4  2011-01-12 04:10:32  brian
 - code updates for 2.6.32 kernel and gcc 4.4

 Revision 1.1.2.3  2010-11-28 14:32:26  brian
 - updates to support debian squeeze 2.6.32 kernel

 Revision 1.1.2.2  2009-07-23 16:37:54  brian
 - updates for release

 Revision 1.1.2.1  2009-06-21 11:37:17  brian
 - added files to new distro

 *****************************************************************************/

static char const ident[] = "$RCSfile: strspecfs.c,v $ $Name:  $($Revision: 1.1.2.11 $) $Date: 2011-09-20 09:51:39 $";

#ifdef NEED_LINUX_AUTOCONF_H
#include NEED_LINUX_AUTOCONF_H
#endif
#include <linux/version.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/compiler.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#if defined HAVE_KINC_LINUX_HARDIRQ_H
#include <linux/hardirq.h>	/* for in_irq() and friends */
#endif
#include <linux/delay.h>
#include <linux/sysctl.h>
#include <linux/file.h>
#include <linux/poll.h>
#include <linux/fs.h>
#ifdef CONFIG_PROC_FS
#include <linux/proc_fs.h>
#endif
#if defined(CONFIG_KMOD) || defined(CONFIG_MODULES)
#include <linux/kmod.h>
#endif
#include <linux/major.h>
#include <asm/atomic.h>

#include <linux/kernel.h>	/* for simple_strtoul, FASTCALL(), fastcall */
#include <linux/pagemap.h>	/* for PAGE_CACHE_SIZE */
#if defined HAVE_KINC_LINUX_NAMEI_H
#include <linux/namei.h>	/* for lookup_hash on 2.6 */
#endif
#include <linux/mount.h>	/* for mntget and friends */

#if defined HAVE_KINC_LINUX_STATFS_H
#include <linux/statfs.h>
#endif
#if defined HAVE_KINC_LINUX_SECURITY_H
#include <linux/security.h>	/* avoid ptrace conflict */
#endif

#include "sys/strdebug.h"

#if ! defined HAVE_KFUNC_MODULE_PUT
#define module_refcount(__m) atomic_read(&(__m)->uc.usecount)
#endif

#include "sys/config.h"

#define SPECFS_DESCRIP		"SVR 4.2 Special Shadow Filesystem (SPECFS)"
#define SPECFS_EXTRA		"Part of UNIX SYSTEM V RELEASE 4.2 FAST STREAMS FOR LINUX"
#define SPECFS_COPYRIGHT	"Copyright (c) 2008-2013  Monavacon Limited.  All Rights Reserved."
#define SPECFS_REVISION		"LfS $RCSfile: strspecfs.c,v $ $Name:  $($Revision: 1.1.2.11 $) $Date: 2011-09-20 09:51:39 $"
#define SPECFS_DEVICE		"SVR 4.2 Special Shadow Filesystem (SPECFS)"
#define SPECFS_CONTACT		"Brian Bidulock <bidulock@openss7.org>"
#define SPECFS_LICENSE		"GPL"
#define SPECFS_BANNER		SPECFS_DESCRIP		"\n" \
				SPECFS_EXTRA		"\n" \
				SPECFS_COPYRIGHT	"\n" \
				SPECFS_REVISION		"\n" \
				SPECFS_DEVICE		"\n" \
				SPECFS_CONTACT		"\n"
#define SPECFS_SPLASH		SPECFS_DEVICE		" - " \
				SPECFS_REVISION		"\n"

#ifdef CONFIG_STREAMS_MODULE
MODULE_AUTHOR(SPECFS_CONTACT);
MODULE_DESCRIPTION(SPECFS_DESCRIP);
MODULE_SUPPORTED_DEVICE(SPECFS_DEVICE);
MODULE_LICENSE(SPECFS_LICENSE);
#if defined MODULE_ALIAS
MODULE_ALIAS("specfs");
#endif
#ifdef MODULE_VERSION
MODULE_VERSION(PACKAGE_ENVR);
#endif
#endif

#ifdef CONFIG_STREAMS_MODULE
#ifdef MODULE_ALIAS
MODULE_ALIAS("/dev/streams");
MODULE_ALIAS("/dev/streams/*");
#endif
#endif

#include <sys/stream.h>
#include <sys/strsubr.h>
#include <sys/strconf.h>
#include <sys/ddi.h>

#include "strlookup.h"		/* for cdevsw_list */
#include "strspecfs.h"		/* for own struct spec_sb_info */
#include "strlock.h"		/* for filesystem signage initialization */

/* 
 *  -------------------------------------------------------------------------
 *
 *  SPEC (Special Device Shadow Filesystem) Ala SVR4.
 *
 *  -------------------------------------------------------------------------
 */

/*
    --------------------------------------------------------------------------------------------------------
                                                                                                             
    Structure layout:                                                                                        
                                                                                                             
      cdevsw              struct cdevsw          struct devnode                                              
    __________               __________                               struct stdata   struct stdata          
   |          |------------>|          |            __________         __________      __________            
   |__________|     ,------>|          |---------->|          |------>|          |--->|          |           
   |          |     |,----->|          |           | non-clone|       |          |    |          |           
   |__________|     ||      |          |       ,---|__________|       |          |    |          |           
   |          |     ||      |__________|       |    __________        |__________|    |__________|           
   |__________|     ||           |             '-->|          |            ^                ^                
   |          |_____||   d_inode |                 |  clone   |            |                |                
   |__________|      |           |             ,---|__________|            |                |                
   |          |      |           |             |    __________             |                |                
   |__________|      |           |             '-->|          |            |                |                
   |          |      |           |                 |          |            |                |                
   |__________|      |           |             ,---|__________|            |                |                
   |          |______|           |             |        |                  |                |                
   |__________|                  |             '-->     | n_inode          |                |                
   |          |                  |                      |                  |                |                
   |__________|                  |                      |                  |                |                
   |          |                  |                      |                  |                |                
   |__________|                  |                      |                  |                |                
   |          |                  |                      |                  |                |                
   |__________|                  |                      |                  |                |                
                                 |                      |                  |                |                
                             ____v_____             ____v_____             |                |                
                    +------>|          |<-.        |          |<--. i_str  |                |                
                    |  ,----|__________|  |        |__________|---|--------'                |                
     sb inode       |  |     __________   |         __________    |                         |                
    __________      |  +--->|          |<-|-.      |          |<--|-.      i_str            |                
   |          |_____|  ,----|__________|  | |      |__________|---|-|-----------------------'                
   |__________|        +--->|          |  | |      |          |<--|-|-.                                      
                       ,----|__________|  | |      |__________|   | | |                                      
                       |     __________   | |       __________    | | |       struct stdata                  
		       +--->|          |  | |      |          |   | | |        __________                    
		       ,----|__________|  | |      |__________|---|-|-|------>|          |                   
                       |                  | |                     | | | i_str |          |                   
                       +---> dir inodes   | |       dev inodes    | | |       |          |                   
                                          | |                     | | |       |__________|                   
                                          | |                     | | |                                      
                             __________   | |       __________    | | |                                      
                     ,----->|          |__| |  /-->|          |___| | |                                      
                     |      |__________|----|-/.---|__________|d_inode|                                      
                     |       __________     |  |    __________      | |                                      
    __________       |----->|          |____|  '-->|          |_____| |                                      
   |          |______|      |__________|       .---|__________|d_inode|                                      
   |__________|      |       __________        '-->|          |-------'                                      
                     |----->|          |       .---|__________|d_inode                                       
    root dentry      |      |__________|       |                                                             
                     |       __________        '-->                                                          
                     '----->|          |       .---                                                          
                            |__________|       |                                                             
                             dir dentry        '--> dev dentry                                               
                                                                                                             
                                                                                                             
    Notes:
                                                                                                             
    - all devices accessed using external device numbers use the cdevsw hash table on the major
      device number, index the cdevsw entry for the major device number.  The internal major device
      number can be calculated using the external major device number and the cdevsw entry.  The
      internal minor device number can also be calculated using the external major and external
      minor.  The minor inode can be found using an iget() lookup by inode number calculated from
      the internal major and minor device numbers.  The i_str  pointer for the inode can be checked
      to see if an stdata structure already exists.  If there is a devnode structure associated with
      the inode (si_node pointer) then minor device specifications and and autopush lists can
      be determined from the devnode structure.  The superblock inode_create operation will create a
      new inode and associate it with a devnode if one exists for the minor device instance.
                                                                                                             
    - if Linux does not find a character device entry for the major device number, it will load the
      "/dev/%s" (with devfs) or "char-major-%d" (without devfs) device which will either establish a
      cdevsw table entry or fail.
                                                                                                             
    - all devices access using the specfs directory hierarchy will enter at the root dentry.
                                                                                                             
    - If the subdirectory dentry equivalent to the STREAMS module name does not exist, i_lookup on
      the superblock inode will attempt to load "/dev/streams/%s" and then "streams-%s" with the
      subdirectory (driver/module) name.   When the kernel module loads and registers the cdevsw
      table entry will be created and the next lookup operation should succeed.  i_lookup uses the
      dentry name to find the cdevsw table entry of the same name and creates an inode for it if one
      does not already exist.  The inode number of the directory inode is the module id.  A cdevsw
      table entry can be found by moduile id with an iget() using the module id as the inode
      number.
                                                                                                             
    - If the device dentry equivalent to the device node name does not exist, i_lookup on the module
      inode will attempt to load "/dev/stream/%s/%s" and then "streams-%s-%s" with the module and
      device instance names.  When the kernel module loads and registers the device name, the
      devnode entry will be created and the next lookup operation should succeed.  i_lookup uses the
      dentry name to find the devnode entry of the same name and creates an inode for it if one
      does not already exist.  The inode number of the device inode is the module id and the device
      instance number concatenated.  A device inode and corresponding devnode can be found with an
      iget() using the module id and instance number as the inode number.
                                                                                                             
    - If the device dentry name is numeric and no other device node can be found, then the number
      will be used as an instance number and the inode acquired using the concatentation of the
      module id and the instance number using iget().  The resulting inode will be attached to the
      dentry.  Device inodes can exist briefly without any devnode structure or dentry.  These
      device inodes are created in response to clone opens when new unique instance numbers are
      assigned that have no associated dentry or devnode.  Because a dentry is ultimately needed for
      the shadow open, to replace the original non-shadow entry, one must be created if it does not
      exist.
                                                                                                             
    --------------------------------------------------------------------------------------------------------
 */

#ifdef HAVE_KMEMB_STRUCT_INODE_I_PRIVATE
#define i_private i_private
#define i_str i_private
#else				/* HAVE_KMEMB_STRUCT_INODE_I_PRIVATE */
#define i_private u.generic_ip
#define i_str i_pipe
#endif				/* HAVE_KMEMB_STRUCT_INODE_I_PRIVATE */

/* we want macro versions of these */

#undef getmajor
#define getmajor(__ino) (((__ino)>>16)&0x0000ffff)

#undef getminor
#define getminor(__ino) (((__ino)>>0)&0x0000ffff)

#undef makedevice
#define makedevice(__maj,__min) ((((__maj)<<16)&0xffff0000)|(((__min)<<0)&0x0000ffff))

#if   defined HAVE_FILE_MOVE_SYMBOL
extern void file_move(struct file *file, struct list_head *list);
#elif defined HAVE_FILE_SB_LIST_ADD_SYMBOL && defined HAVE_FILE_SB_LIST_DEL_SYMBOL
extern void file_sb_list_add(struct file *file, struct super_block *sb);
extern void file_sb_list_del(struct file *file);
#else
#error Need a way to move a file pointer.
#endif

STATIC struct vfsmount *specfs_mnt = NULL;

/*
 *  -------------------------------------------------------------------------
 *  -------------------------------------------------------------------------
 */
STATIC void spec_read_inode(struct inode *);

BIG_STATIC struct inode *
spec_snode(dev_t dev, struct cdevsw *cdev)
{
	struct inode *snode;
	struct super_block *sb;

	assert(specfs_mnt);
	sb = specfs_mnt->mnt_sb;

#if defined HAVE_KFUNC_IGET_LOCKED
	if (!(snode = iget_locked(sb, dev))) {
		_ptrace(("couldn't allocate snode\n"));
		return ERR_PTR(-ENOMEM);
	} else {
		if (snode->i_state & I_NEW) {
			/* just a way to pass another argument to read_inode() */
			snode->i_private = cdev;
#if defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_READ_INODE
			sb->s_op->read_inode(snode);
#else
			spec_read_inode(snode);
#endif
			unlock_new_inode(snode);
		}
	}
#else
	if (!(snode = iget4(sb, dev, NULL, cdev))) {
		_ptrace(("couldn't allocate inode\n"));
		return ERR_PTR(-ENOMEM);
	}
#endif
	_ptrace(("inode %p no %lu refcount now %d\n", snode, snode->i_ino,
		 atomic_read(&snode->i_count)));
	return (snode);
}

#if defined HAVE_KMEMB_STRUCT_DENTRY_OPERATIONS_D_DNAME && ! defined HAVE_KMEMB_STRUCT_SUPER_BLOCK_S_D_OP
static const struct dentry_operations spec_root_d_ops;
#endif

streams_fastcall int
spec_reparent(struct file *file, struct cdevsw *cdev, dev_t dev)
{
	struct inode *snode;
	struct dentry *dentry;
	struct vfsmount *mnt;
	int err;

	if (file == NULL) {
		ptrace(("Error path taken!\n"));
		return (-EFAULT);
	}
	if (cdev == NULL) {
		ptrace(("Error path taken!\n"));
		return (-EFAULT);
	}

	if (!(mnt = mntget(specfs_mnt))) {
		ptrace(("Error path taken!\n"));
		return (-ENODEV);
	}
	{
#ifdef HAVE_KMEMB_STRUCT_DENTRY_OPERATIONS_D_DNAME
		struct qstr name = { .name = "" };
#else				/* HAVE_KMEMB_STRUCT_DENTRY_OPERATIONS_D_DNAME */
		struct devnode *cmin;
		struct qstr name;
		char buf[25];

		name.name = (typeof(name.name)) buf;
		if ((cmin = cmin_get(cdev, getminor(dev))))
			name.len = snprintf(buf, sizeof(buf), "STR %s/%s",
					    cdev->d_name, cmin->n_name);
		else
			name.len = snprintf(buf, sizeof(buf), "STR %s/%lu",
					    cdev->d_name, getminor(dev));
#endif				/* HAVE_KMEMB_STRUCT_DENTRY_OPERATIONS_D_DNAME */
#ifdef HAVE_KFUNC_D_ALLOC_PSEUDO
		if (!(dentry = d_alloc_pseudo(mnt->mnt_sb, &name))) {
			ptrace(("Error path taken!\n"));
			err = -ENOMEM;
			goto mnt_error;
		}
#else				/* HAVE_KFUNC_D_ALLOC_PSEUDO */
		if (!(dentry = d_alloc(NULL, &name))) {
			ptrace(("Error path taken!\n"));
			err = -ENOMEM;
			goto mnt_error;
		}
		dentry->d_sb = mnt->mnt_sb;
		dentry->d_parent = dentry;  /* root dentry */
#ifdef DCACHE_DISCONNECTED
		dentry->d_flags |= DCACHE_DISCONNECTED;
#else
		dentry->d_flags &= ~(DCACHE_UNHASHED);
#endif
#endif				/* HAVE_KFUNC_D_ALLOC_PSEUDO */
#if defined HAVE_KMEMB_STRUCT_DENTRY_OPERATIONS_D_DNAME && ! defined HAVE_KMEMB_STRUCT_SUPER_BLOCK_S_D_OP
		dentry->d_op = &spec_root_d_ops;
#endif
	}

	if (IS_ERR((snode = spec_snode(dev, cdev)))) {
		ptrace(("Error path taken!\n"));
		err = PTR_ERR(snode);
		goto put_error;
	}
	d_instantiate(dentry, snode);

	err = -ENXIO;
	if (!snode || !snode->i_fop || !snode->i_fop->open) {
		ptrace(("Error path taken!\n"));
		goto put_error;
	}

	{
		const struct file_operations *f_op;

		if (!(f_op = fops_get(snode->i_fop))) {
			ptrace(("Error path taken!\n"));
			goto put_error;
		}
#ifdef _DEBUG
		if (f_op->owner)
			printd(("%s: [%s] new f_ops count is now %d\n", __FUNCTION__,
				 f_op->owner->name, module_refcount(f_op->owner)));
		else
			printd(("%s: new f_ops have no owner!\n", __FUNCTION__));
#endif
#ifdef _DEBUG
		if (file->f_op->owner)
			printd(("%s: [%s] old f_ops count is now %d\n", __FUNCTION__,
				 file->f_op->owner->name, module_refcount(file->f_op->owner) - 1));
		else
			printd(("%s: old f_ops have no owner!\n", __FUNCTION__));
#endif
		fops_put(file->f_op);
		file->f_op = (struct file_operations *) f_op;
	}
	if (file->f_dentry != NULL)
		dput(file->f_dentry);
	file->f_dentry = dentry;
	if (file->f_vfsmnt != NULL)
		mntput(file->f_vfsmnt);
	file->f_vfsmnt = mnt;
#if   defined HAVE_FILE_MOVE_SYMBOL
	file_move(file, &mnt->mnt_sb->s_files);
#elif defined HAVE_FILE_SB_LIST_ADD_SYMBOL
	file_sb_list_del(file);
	file_sb_list_add(file, mnt->mnt_sb);
#else
#error Need a way to move a file pointer.
#endif
	return (0);

      put_error:
	dput(dentry);
      mnt_error:
	mntput(mnt);
	return (err);
}

EXPORT_SYMBOL_GPL(spec_reparent);

streams_fastcall int
spec_open(struct file *file, struct cdevsw *cdev, dev_t dev, int sflag)
{
	struct dentry *dentry;
	struct vfsmount *mnt;
	int err;

	/* I wish dentry_open() would use what's in the file pointer instead of what it has in
	   local variables */
	dentry = dget(file->f_dentry);
	mnt = mntget(file->f_vfsmnt);

	if (!(err = spec_reparent(file, cdev, dev))) {
		file->f_flags =
		    (sflag == CLONEOPEN) ? (file->f_flags | O_CLONE) : (file->f_flags & ~O_CLONE);
		err = file->f_op->open(file->f_dentry->d_inode, file);
		file->f_flags &= ~O_CLONE;
		if (!err) {
			dput(dentry);
			mntput(mnt);
			return (0);

		} else
			_ptrace(("Error path taken!\n"));
	} else
		_ptrace(("Error path taken!\n"));

	dput(file->f_dentry);
	mntput(file->f_vfsmnt);
	return (err > 0 ? -err : err);
}

EXPORT_SYMBOL_GPL(spec_open);

/* 
 *  =========================================================================
 *
 *  Shadow Special Filesystem Module directory
 *
 *  =========================================================================
 */
/*
 *  Shadow Special Filesystem Module directory inode operations.
 *  -------------------------------------------------------------------------
 */
/**
 *  spec_dir_i_lookup:	- lookup a device in a driver/module subdirectory
 *  @dir:		inode of the driver subdirectory
 *  @new:		directory entry for which to search for a device inode
 *
 *  In the shadow special filesystem, each directory corresponds to a registered STREAMS device.
 *  The inode numbers of these directories are made up of '0' as the major device number and the
 *  first registered major device number as the minor device number.  Whenever a STREAMS device is
 *  registered, it appears under the root directory.  We hang the cdevsw table entry off of the
 *  i_private pointer (but we could actually put it right inside the inode).
 *
 *  if someone goes to look up a name in a specific device directory and the name does not exist, we
 *  try to load a module with the name streams-%s-%s.o where the first string is the major device
 *  name and the second string is the minor device name.  We also do a similar thing on the root
 *  directory for autoloading devices.  Then we just repeat the lookup and echo back whatever
 *  appeared (or didn't).
 *
 *  Directory inodes can exist after the module has been unloaded, so we cannot use the i_private
 *  pointer, we need to get the cdev entry from the inode number again.
 */
#if defined HAVE_INODE_OPERATIONS_LOOKUP_NAMEIDATA
STATIC struct dentry *
spec_dir_i_lookup(struct inode *dir, struct dentry *new, struct nameidata *dummy)
#else
STATIC struct dentry *
spec_dir_i_lookup(struct inode *dir, struct dentry *new)
#endif
{
	struct cdevsw *cdev;

	_ptrace(("looking up %s\n", new->d_name.name));
	if ((cdev = cdrv_get(getminor(dir->i_ino)))) {
		struct devnode *cmin;

		_ptrace(("found cdev %s\n", cdev->d_name));
		/* check if the name is registered as a minor device node name */
		if ((cmin = cmin_find(cdev, (char *) new->d_name.name))) {
			struct inode *inode;

			_ptrace(("found cmin %s\n", cmin->n_name));
			if ((inode = cmin->n_inode)) {
				_ptrace(("found inode for cmin %s\n", cmin->n_name));
				igrab(inode);
				_ptrace(("inode %p no %lu refcount now %d\n", inode, inode->i_ino,
					 atomic_read(&inode->i_count)));
				d_add(new, inode);
				_ctrace(cdrv_put(cdev));
				return (NULL);	/* success */
			}
			_ptrace(("no inode for cmin %s\n", cmin->n_name));
			_ctrace(cdrv_put(cdev));
			return ERR_PTR(-EIO);
		} else {
			/* check if the name is a valid number */
			char *tail = (char *) new->d_name.name;
			minor_t minor = simple_strtoul(tail, &tail, 10);	/* base 10 only! */

			if (*tail == '\0') {
				if ((minor & ~MINORMASK) == 0) {
					struct inode *inode;
					dev_t dev = makedevice(cdev->d_modid, minor);

					_ptrace(("looking up inode for number %s\n",
						 new->d_name.name));
					if (IS_ERR((inode = spec_snode(dev, cdev)))) {
						_ptrace(("no inode for number %s\n",
							 new->d_name.name));
						_ctrace(cdrv_put(cdev));
						return ((struct dentry *) inode);
						/* already contains error */
					}
					_ptrace(("found inode for number %s\n", new->d_name.name));
					d_add(new, inode);
					_ctrace(cdrv_put(cdev));
					return (NULL);	/* success */
				}
			}
		}
		_ptrace(("no inode for %s\n", new->d_name.name));
		_ctrace(cdrv_put(cdev));
	}
	return ERR_PTR(-ENOENT);
}

 /* TODO: we can make links in this directory.  We just have to instantiate a devnode minor device
    node structure and attach it to the cdevsw structure and assign it the appropriate minor device 
    number.  That would be quite simple. */

STATIC struct inode_operations spec_dir_i_ops = {
	lookup:spec_dir_i_lookup,
};

/* 
 *  Shadow Special Filesystem Module directory file operations.
 *  -------------------------------------------------------------------------
 */

/**
 *  spec_dir_readdir:	- read a driver/module subdirectory
 *  @file:		user file pointer
 *  @dirent:		pointer to user directory entry array
 *  @filldir:		procedure for filling the directory entries
 *
 *  Lists a driver subdirectory.  The driver subdirectory contains registered minor device nodes and
 *  active (open) devices.  spec_dir_readdir() walks the allocated device node list and then the
 *  active stream head list associated with the driver.
 */
STATIC int
spec_dir_readdir(struct file *file, void *dirent, filldir_t filldir)
{
	struct dentry *dentry = file->f_dentry;
	int nr = file->f_pos;

	switch (nr) {
		struct cdevsw *cdev;

	case 0:
		if (filldir(dirent, ".", 1, nr, dentry->d_inode->i_ino, DT_DIR) < 0)
			break;
		nr++;
		file->f_pos++;
		/* fall through */
	case 1:
		if (filldir(dirent, "..", 2, nr, dentry->d_parent->d_inode->i_ino, DT_DIR) < 0)
			break;
		nr++;
		file->f_pos++;
		/* fall through */
	default:
		/* Cannot take cdevsw structure pointer from the snode because the directory inode
		   might exist even though the module is unloaded.  So we need to look it up again, 
		   but without locks... */
		if ((cdev = cdrv_get(getminor(dentry->d_inode->i_ino)))) {
			int i = nr - 2, err = 0;

			read_lock(&cdevsw_lock);
			if (cdev->d_minors.next && !list_empty(&cdev->d_minors)) {
				struct list_head *pos;

				/* skip to position */
				for (pos = cdev->d_minors.next; pos != &cdev->d_minors && i;
				     pos = pos->next, i--) ;
				/* start writing */
				for (; err >= 0 && pos != &cdev->d_minors;
				     pos = pos->next, nr++, file->f_pos++) {
					struct devnode *cmin =
					    list_entry(pos, struct devnode, n_list);

					if (cmin->n_inode == NULL)
						continue;

					read_unlock(&cdevsw_lock);	/* Not safe */
					err = filldir(dirent, cmin->n_name,
						      strnlen(cmin->n_name, FMNAMESZ),
						      file->f_pos, cmin->n_inode->i_ino,
						      cmin->n_inode->i_mode >> 12);
					read_lock(&cdevsw_lock);
				}
			}
			/* walk the active stream head list */
			if (cdev->d_stlist.next && !list_empty(&cdev->d_stlist)) {
				struct list_head *pos;

				/* skil to position */
				for (pos = cdev->d_stlist.next; pos != &cdev->d_stlist && i;
				     pos = pos->next, i--) ;
				for (; err >= 0 && pos != &cdev->d_stlist;
				     pos = pos->next, nr++, file->f_pos++) {
					struct stdata *sd = list_entry(pos, struct stdata, sd_list);
					char numstr[24];
					int len;

					if (sd->sd_inode == NULL)
						continue;

					len = snprintf(numstr, sizeof(numstr),
						       "%lu", getminor(sd->sd_inode->i_ino));

					read_unlock(&cdevsw_lock);	/* Not safe */
					err = filldir(dirent, numstr, len,
						      file->f_pos,
						      sd->sd_inode->i_ino,
						      sd->sd_inode->i_mode >> 12);
					read_lock(&cdevsw_lock);
				}
			}
			read_unlock(&cdevsw_lock);
			_ctrace(cdrv_put(cdev));
		}
		break;
	}
	return (0);
}

STATIC struct file_operations spec_dir_f_ops = {
	.owner = THIS_MODULE,
	.read = generic_read_dir,
	.readdir = spec_dir_readdir,
};

/* 
 *  =========================================================================
 *
 *  Shadow Special Filesystem ROOT
 *
 *  =========================================================================
 */
/*
 *  Shadow Special Filesystem Root inode operations.
 *  -------------------------------------------------------------------------
 */
/**
 *  spec_root_i_lookup:	- look up a subdirectory module inode
 *  @dir:		inode for the root directory
 *  @dentry:		directory entry to look up
 *
 *  The lookup() method is called on directory inodes (in our case the root) when a cached_lookup()
 *  of the dentry fails on the name.  We are given a newly created dentry, "new", that has no inode.
 *  We lookup the inode by name from the module switch table and then look up the inode by module id
 *  from the device/module switch table entry from the super block.  The iget() called here will
 *  check the inode hash an either find an existing inode, or it invokes the superblock
 *  spec_read_inode() operation, below, that will create a new inode.  We only fail to get an inode
 *  when the inode allocate fails -%ENOMEM.
 *
 *  When we get here we either do not have an inode associated with the dentry name, or there is
 *  simply no dentry in the dentry cache for this inode yet.  We walk through the cdevsw list
 *  looking for the dentry name.  If we find one, we lookup or create a inode with the inode number
 *  equal to the module id and return that inode for attachment to the dentry.  If the name cannot
 *  be found and the name is numeric, we check again with the module id equal to the numeric name.
 *  If we cannot find a corresponding cdevsw entry and we are configured for kernel module loading,
 *  we request a module of the name streams-%s, where %s is the name requested.
 */
#if defined HAVE_INODE_OPERATIONS_LOOKUP_NAMEIDATA
STATIC struct dentry *
spec_root_i_lookup(struct inode *dir, struct dentry *new, struct nameidata *dummy)
#else
STATIC struct dentry *
spec_root_i_lookup(struct inode *dir, struct dentry *new)
#endif
{
	struct cdevsw *cdev;

	_ptrace(("looking up %s\n", new->d_name.name));
	/* this will also attempt to demand load the "streams-%s" module if required */
	if ((cdev = cdev_find((char *) new->d_name.name))) {
		struct inode *inode;

		_ptrace(("found cdev %s\n", cdev->d_name));
		if ((inode = cdev->d_inode)) {
			_ptrace(("found inode for cdev %s\n", cdev->d_name));
			igrab(inode);
			_ptrace(("inode %p no %lu refcount now %d\n", inode, inode->i_ino,
				 atomic_read(&inode->i_count)));
			_ctrace(sdev_put(cdev));
			d_add(new, inode);
			return (NULL);	/* success */
		}
		/* It must be a module.  This has the rather unwanted side-effect that searching
		   directory %s could demand load streams-%s, where streams-%s is not a driver but
		   a module. */
		_ptrace(("no inode for cdev %s\n", cdev->d_name));
		_ctrace(sdev_put(cdev));
	} else
		_ptrace(("no cdev for %s\n", new->d_name.name));
	return ERR_PTR(-ENOENT);
}

STATIC struct inode_operations spec_root_i_ops = {
	lookup:spec_root_i_lookup,
};

/* 
 *  Shadow Special Filesystem Root file operations.
 *  -------------------------------------------------------------------------
 */

/**
 *  spec_root_readdir:	- read the root directory
 *  @file:		user file pointer
 *  @dirent:		pointer to user directory entry array
 *  @filldir:		procedure for filling the directory entries
 *
 *  Lists the root directory.  The root directory contains subdirectories for each device in the
 *  cdevsw hash.  It walks the cdevsw_list and fills a dirent structure for each item on the list.
 *  Each cdevsw entry that has an associated directory inode is listed.
 */
STATIC int
spec_root_readdir(struct file *file, void *dirent, filldir_t filldir)
{
	struct dentry *dentry = file->f_dentry;
	int nr = file->f_pos;

	switch (nr) {
	case 0:
		if (filldir(dirent, ".", 1, nr, dentry->d_inode->i_ino, DT_DIR) < 0)
			break;
		nr++;
		file->f_pos++;
		/* fall through */
	case 1:
		if (filldir(dirent, "..", 2, nr, dentry->d_parent->d_inode->i_ino, DT_DIR) < 0)
			break;
		nr++;
		file->f_pos++;
		/* fall through */
	default:
		read_lock(&cdevsw_lock);
		if (cdevsw_list.next) {
			struct list_head *pos;
			int i = nr - 2, err = 0;

			/* skip to position */
			for (pos = cdevsw_list.next; pos != &cdevsw_list && i;
			     pos = pos->next, i--) ;
			/* start writing */
			for (; err >= 0 && pos != &cdevsw_list;
			     pos = pos->next, nr++, file->f_pos++) {
				struct cdevsw *cdev = list_entry(pos, struct cdevsw, d_list);

				if (cdev->d_inode) {
					read_unlock(&cdevsw_lock);
					err = filldir(dirent, cdev->d_name,
						      strnlen(cdev->d_name, FMNAMESZ), file->f_pos,
						      cdev->d_inode->i_ino,
						      (cdev->d_inode->i_mode >> 12) & 15);
					read_lock(&cdevsw_lock);
				}
			}
		}
		read_unlock(&cdevsw_lock);
		break;
	}
	return 0;
}

STATIC struct file_operations spec_root_f_ops = {
	.owner = THIS_MODULE,
	.read = generic_read_dir,
	.readdir = spec_root_readdir,
};

/*
 *  Shadow Special Filesystem Dentry operations
 *  -------------------------------------------------------------------------
 */

#if defined HAVE_KMEMB_STRUCT_DENTRY_OPERATIONS_D_DNAME || !defined DCACHE_DISCONNECTED
#ifdef HAVE_KMEMB_STRUCT_DENTRY_OPERATIONS_D_DNAME
/**
 *  spec_dname:	- provide dynamic dentry path name
 *  @dentry:	dentry for which to provide path name
 */
static char *
specfs_dname(struct dentry *dentry, char *buffer, int buflen)
{
	struct cdevsw *cdev;

	if ((cdev = cdrv_get(getmajor(dentry->d_inode->i_ino)))) {
		struct devnode *cmin;

		if ((cmin = cmin_get(cdev, getminor(dentry->d_inode->i_ino)))) {
			return dynamic_dname(dentry, buffer, buflen, "STR %s/%s", cdev->d_name, cmin->n_name);
		} else {
			return dynamic_dname(dentry, buffer, buflen, "STR %s/%lu", cdev->d_name,
					     getminor(dentry->d_inode->i_ino));
		}
	} else {
		return dynamic_dname(dentry, buffer, buflen, "STR ???/???");
	}
}
#endif				/* CONFIG_KMEMB_STRUCT_DENTRY_OPERATIONS_D_DNAME */

#ifndef DCACHE_DISCONNECTED
static int specfs_delete_dentry(struct dentry *dentry)
{
	dentry->d_flags |= DCACHE_UNHASHED;
	return 0;
}
#endif

static const struct dentry_operations spec_root_d_ops = {
#ifndef DCACHE_DISCONNECTED
	.d_delete = specfs_delete_dentry,
#endif
#ifdef HAVE_KMEMB_STRUCT_DENTRY_OPERATIONS_D_DNAME
	.d_dname = specfs_dname,
#endif
};
#endif

/* 
 *  =========================================================================
 *
 *  Shadow Special Filesystem super block.
 *
 *  =========================================================================
 */
/* 
 *  Shadow Special Filesystem super block.
 *  -------------------------------------------------------------------------
 */

#if defined HAVE_KMEMB_STRUCT_SUPER_BLOCK_S_FS_INFO
#define SPECFS_SB(s) s->s_fs_info
#elif defined HAVE_KMEMB_STRUCT_SUPER_BLOCK_U_GENERIC_SBP
#define SPECFS_SB(s) s->u.generic_sbp
#else
#error HAVE_KMEMB_STRUCT_SUPER_BLOCK_S_FS_INFO or HAVE_KMEMB_STRUCT_SUPER_BLOCK_U_GENERIC_SBP must be defined.
#endif

STATIC struct spec_sb_info *
spec_sbi_alloc(void)
{
	struct spec_sb_info *sbi;

	if ((sbi = kmalloc(sizeof(*sbi), GFP_ATOMIC))) {
		memset(sbi, 0, sizeof(*sbi));
		sbi->sbi_magic = SPEC_SBI_MAGIC;
	}
	return (sbi);
}

STATIC void
spec_sbi_free(struct spec_sb_info *sbi)
{
	if (sbi) {
		sbi->sbi_magic = 0;
		kfree(sbi);
	}
}

/**
 *  spec_parse_options: - parse shadow special filesystem options
 *  @options:	character string of options
 *  @sbi:	pointer to a superblock information structure
 *
 *  Parses the character string options and places the parsed values into the supplied shadow
 *  special filesystem superblock information structure.  If option processing fails, reasonable
 *  values will be assigned to all super block options.
 */
STATIC int
spec_parse_options(char *options, struct spec_sb_info *sbi)
{
	int err = 0;
	int setuid = 0;
	int setgid = 0;
	int setmod = 0;
	uid_t uid = 0;
	uid_t gid = 0;
	umode_t mode = 0777;
	char *this_char, *value, *token = options;

	if (!sbi || sbi->sbi_magic != SPEC_SBI_MAGIC)
		goto einval;
	while ((this_char = strsep(&token, ","))) {
		if ((value = strchr(this_char, '=')) != NULL)
			*value++ = 0;
		if (!strcmp(this_char, "uid")) {
			if (!value || !*value)
				goto einval;
			uid = simple_strtoul(value, &value, 0);
			if (*value)
				goto einval;
			setuid = 1;
		} else if (!strcmp(this_char, "gid")) {
			if (!value || !*value)
				goto einval;
			gid = simple_strtoul(value, &value, 0);
			if (*value)
				goto einval;
			setgid = 1;
		} else if (!strcmp(this_char, "mode")) {
			if (!value || !*value)
				goto einval;
			mode = simple_strtoul(value, &value, 0);
			if (*value)
				goto einval;
			setmod = 1;
		} else
			goto einval;
	}
      done_options:
	sbi->sbi_setuid = setuid;
	sbi->sbi_setgid = setgid;
	sbi->sbi_setmod = setmod;
	sbi->sbi_uid = uid;
	sbi->sbi_gid = gid;
	sbi->sbi_mode = mode & ~S_IFMT;
	return (err);
      einval:
	err = -EINVAL;
	goto done_options;
}

#if defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_SHOW_OPTIONS

/**
 *  spec_show_options:	- show shadow special filesystem options
 *  @seq:		sequence file
 *  @vfs:		vfs mount
 */
STATIC int
spec_show_options(struct seq_file *seq, struct vfsmount *vfs)
{
	struct spec_sb_info *sbi = SPECFS_SB(vfs->mnt_sb);
	
	if (sbi != NULL) {
		if (sbi->sbi_setuid)
			seq_printf(seq, ",uid=%u", sbi->sbi_uid);
		if (sbi->sbi_setgid)
			seq_printf(seq, ",gid=%u", sbi->sbi_gid);
		if (sbi->sbi_setmod)
			seq_printf(seq, ",mode=%03o", sbi->sbi_mode);
	}
	return 0;
}

#endif				/* defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_SHOW_OPTIONS */

/**
 *  spec_read_inode: - read a inode from the filesystem
 *  @inode:	initialized inode to read
 *
 *  The read_inode() method is called on the superblock when we cannot find an inode by inode number
 *  in the inode hashes for the super block.  A fresh inode is created with the inode number
 *  requested and then this method is called to "read" the inode.
 *
 *  For module nodes, the major component of the inode number is zero indicating that this is a
 *  module node; the minor component of the inode number is the module id.  For device nodes, the
 *  major component of the inode number is the module id; the minor component of the inode number is
 *  the device instance.
 *
 *  We use the inode number in this way to determine if the inode is for a module node or whether it
 *  is for a device node and then construct and format the inode accordingly.  We don't call
 *  init_special_inode but get the char_device ourselves and populate the inode.  We then populate
 *  all the operations with our own.  Finally we hash the inode.  The inode is returned to iget() in
 *  the inode lookup() method on the specfs root directory or module directory.
 */
STATIC void
spec_read_inode(struct inode *inode)
{
	struct cdevsw *cdev = inode->i_private;

	/* i_private is just another way of passing another argument to iget() */
	_printd(("%s: reading inode %p no %lu\n", __FUNCTION__, inode, inode->i_ino));
	if (!cdev)
		goto bad_inode;
	else {
		struct spec_sb_info *sbi = SPECFS_SB(inode->i_sb);

		inode->i_mode = (sbi->sbi_mode & ~S_IFMT);
		inode->i_uid = sbi->sbi_uid;
		inode->i_gid = sbi->sbi_gid;
	}
	if (getmajor(inode->i_ino)) {
		dev_t dev = MKDEV(cdev->d_major, getminor(inode->i_ino) & MINORMASK);

		/* XXX: To handle the special case of clone devices, where the minor component of
		   the internal device number is the module identifier of the major device to open,
		   check if cdev has a minor device with a (non-zero) module id the same as the
		   minor device component.  If one exists, use the n_minor component of that device.
		   What is done right now is to simply use the external major device number as the
		   internal minor number.  Unfortunately, this means that all clone drivers need an
		   external major device number. */
		/* XXX: Another approach is to make module identifiers to major nodes equal to the
		   external major device number and the point would be moot. */
		_printd(("%s: reading minor device inode %lu\n", __FUNCTION__,
			 (ulong) getminor(inode->i_ino)));
		/* for device nodes, the major component of the i_ino is the module id */
		inode->i_mode |= (cdev->d_mode & S_IFMT) ? (cdev->d_mode & S_IFMT) : S_IFCHR;
		inode->i_mode &= ~S_IXUGO;
#if defined HAVE_KFUNC_TO_KDEV_T
		inode->i_rdev = to_kdev_t(dev);
#else
		inode->i_rdev = dev;
#endif
		inode->i_op = inode->i_op;	/* leave at empty_iops */
		inode->i_fop = cdev->d_fop;
	} else {
		_printd(("%s: reading major device inode %lu\n", __FUNCTION__,
			 (ulong) getminor(inode->i_ino)));
		/* for module nodes, the minor component of the i_ino is the module id */
		inode->i_mode |= S_IFDIR;
		inode->i_mode |= ((inode->i_mode & S_IRUGO) >> 2);
		inode->i_op = &spec_dir_i_ops;
		inode->i_fop = &spec_dir_f_ops;
		inode->i_nlink = 2;
	}
	inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME;
	inode->i_private = NULL;	/* done with it */
	return;
      bad_inode:
	_ptrace(("bad inode no %lu\n", inode->i_ino));
	make_bad_inode(inode);
	return;
}

#if defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_READ_INODE2
/**
 *  spec_read_inode2: - read a inode from the filesystem
 *  @inode:	initialized inode to read
 *
 *  The read_inode2() method is called on the superblock when we cannot find an inode by inode number
 *  in the inode hashes for the super block.  A fresh inode is created with the inode number
 *  requested and then this method is called to "read" the inode.
 *
 *  For module nodes, the major component of the inode number is zero indicating that this is a
 *  module node; the minor component of the inode number is the module id.  For device nodes, the
 *  major component of the inode number is the module id; the minor component of the inode number is
 *  the device instance.
 *
 *  We use the inode number in this way to determine if the inode is for a module node or whether it
 *  is for a device node and then construct and format the inode accordingly.  We don't call
 *  init_special_inode but get the char_device ourselves and populate the inode.  We then populate
 *  all the operations with our own.  Finally we hash the inode.  The inode is returned to iget() in
 *  the inode lookup() method on the specfs root directory or module directory.
 */
STATIC void
spec_read_inode2(struct inode *inode, void *opaque)
{
	inode->i_private = opaque;
	return spec_read_inode(inode);
}
#endif

#if defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_PUT_INODE
/**
 *  spec_put_inode: - put an inode to the filesystem
 *  @inode:	inode to put
 *
 *  The put_inode() superblock operation is called whenever performing iput() on an inode, and
 *  before checking i_nlink on an inode if the i_count has dropped to zero.  This is our chance to
 *  set the number of links to zero so that the inode will just be destroyed (and delete_inode()
 *  below will be called as well).  A force delete here will just set i_nlink to zero if the
 *  i_count is at 1.
 */
STATIC void
spec_put_inode(struct inode *inode)
{
	/* all specfs inodes self destruct when put for the last time */
	_printd(("%s: put of inode %p no %lu\n", __FUNCTION__, inode, inode->i_ino));
	_printd(("%s: inode %p no %lu refcount now %d\n", __FUNCTION__, inode, inode->i_ino,
		 atomic_read(&inode->i_count) - 1));
	if (inode->i_nlink != 0) {
		/* This should not happen because we decrement i_nlink when we remove the STREAM
		   head.  The inode should never be able to go away with a STREAM head attached. */
#if defined HAVE_KFUNC_FORCE_DELETE
		force_delete(inode);
#else
		if (atomic_read(&inode->i_count) == 1) {
			_printd(("%s: final put of inode %p no %lu\n", __FUNCTION__, inode,
				 inode->i_ino));
			inode->i_nlink = 0;
		}
#endif
	}
}
#endif				/* defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_PUT_INODE */

/**
 *  spec_put_super: - put a superblock for the filesystem
 *  @sb:	super block to put
 *
 *  When we put a super block away, we must detach the options structure from the superblock and
 *  free it.
 */
STATIC void
spec_put_super(struct super_block *sb)
{
	/* just free our optional mount information */
	spec_sbi_free(SPECFS_SB(sb));
	SPECFS_SB(sb) = NULL;
}

#define SPECFS_MAGIC 0xDEADBEEF

/**
 *  spec_statfs: - provide statfs information
 *  @sb:	super block
 *  @buf:	buffer for statfs data
 */
#if defined HAVE_SUPER_OPERATIONS_STATFS_DENTRY
STATIC int
spec_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	buf->f_type = dentry->d_sb->s_magic;
	buf->f_bsize = PAGE_CACHE_SIZE;
	buf->f_namelen = NAME_MAX;
	return 0;
}
#else				/* defined HAVE_SUPER_OPERATIONS_STATFS_DENTRY */
#if defined HAVE_KMEMB_STRUCT_KSTATFS_F_TYPE
STATIC int
spec_statfs(struct super_block *sb, struct kstatfs *buf)
#else
STATIC int
spec_statfs(struct super_block *sb, struct statfs *buf)
#endif
{
	buf->f_type = sb->s_magic;
	buf->f_bsize = PAGE_CACHE_SIZE;
	buf->f_namelen = NAME_MAX;
	return 0;
}
#endif				/* defined HAVE_SUPER_OPERATIONS_STATFS_DENTRY */

/**
 *  spec_remount_fs: - remount the shadow special filesystem
 *  @sb:	super block
 *  @flags:	flags
 *  @data:	options data
 *
 *  Notices: When we are remounted, we must check for new options.
 */
STATIC int
spec_remount_fs(struct super_block *sb, int *flags, char *data)
{
	struct spec_sb_info *sbi = SPECFS_SB(sb);

	(void) flags;
	return (data ? spec_parse_options(data, sbi) : 0);
}

#if 0
STATIC void
spec_umount_begin(struct super_block *sb)
{
	(void) sb;
	return;
}
#endif

STATIC kmem_cachep_t snode_cachep = NULL;

/**
 *  spec_alloc_inode: - allocate an inode for the special shadow filesystem.
 *  @sb: filesystem super block
 *
 *  Traditionally the specfs did not allocate its own inodes although the ability (super_operations
 *  alloc_inode) has existed from early 2.4 kernels.  The inode diet of later 2.6 kernels forced
 *  using the i_private pointer instead of the i_pipe pointer for Stream heads (an approach that
 *  does not work for earlier kernels that have a full 'u' union); therefore, requiring that specfs
 *  specific pointers be allocated beyond the inode structure.
 *
 *  This approach has the beneficial side effect that Stream head performance should increase
 *  because snodes are now memory cached in their own cache.
 *
 *  It is quite simply really and should have been done before.
 */
STATIC struct inode *
spec_alloc_inode(struct super_block *sb)
{

	return ((struct inode *) kmem_cache_alloc(snode_cachep, GFP_KERNEL));
}

/**
 *  spec_destroy_inode: - deallocate an inode for the specfs.
 *  @inode: inode to deallocate.
 *
 *  See discussion under spec_alloc_inode().
 */
STATIC void
spec_destroy_inode(struct inode *inode)
{
	if (inode)
		kmem_cache_free(snode_cachep, inode);
}

STATIC struct super_operations spec_s_ops ____cacheline_aligned = {
	.alloc_inode = spec_alloc_inode,
	.destroy_inode = spec_destroy_inode,
#if defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_READ_INODE
	.read_inode = spec_read_inode,
#endif
#if defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_READ_INODE2
	.read_inode2 = spec_read_inode2,
#endif				/* defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_READ_INODE2 */
#if defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_PUT_INODE
	.put_inode = spec_put_inode,
#endif				/* defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_PUT_INODE */
	.put_super = spec_put_super,
	.statfs = spec_statfs,	/* like simple_statfs */
	.remount_fs = spec_remount_fs,
#if 0
	.umount_begin = spec_umount_begin,
#endif
#if defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_SHOW_OPTIONS
	.show_options = spec_show_options,
#endif				/* defined HAVE_KMEMB_STRUCT_SUPER_OPERATIONS_SHOW_OPTIONS */
};

/* TODO: handle extended attributes */
/**
 *  specfs_fill_super: - create a shadow special filesystem super block
 *  @sb:	superblock for which to read a superblock inode
 *  @data:	options data
 *  @silent:	whether to ignore options errors
 *
 *  Create the super block inode.
 */
STATIC int
specfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct inode *inode;
	struct spec_sb_info *sbi;
	int err;

	_ptrace(("filling superblock %p\n", sb));
	sb->s_blocksize = 1024;
	sb->s_blocksize_bits = 10;
	sb->s_magic = SPECFS_MAGIC;
#ifdef HAVE_KMEMB_STRUCT_SUPER_BLOCK_S_TIME_GRAN
	sb->s_time_gran = 1;
#endif
	sb->s_op = &spec_s_ops;
	err = -ENOMEM;
	/* need to read options on mount */
	if (!(sbi = spec_sbi_alloc()))
		goto error;
	if ((err = spec_parse_options(data, sbi)) < 0 && !silent)
		goto free_error;
	err = -ENOMEM;
	if (!(inode = new_inode(sb)))
		goto free_error;
	inode->i_ino = -1UL;	/* unused (non-zero) inode number */
	inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME;
	inode->i_blocks = 0;
#ifdef HAVE_KMEMB_STRUCT_INODE_I_BLKSIZE
	inode->i_blksize = 1024;
#endif
	inode->i_uid = inode->i_gid = 0;
	inode->i_mode = S_IFDIR | S_IRUGO | S_IXUGO | S_IWUSR;
	inode->i_op = &spec_root_i_ops;
	inode->i_fop = &spec_root_f_ops;
	inode->i_nlink = 2;
	if (!(sb->s_root = d_alloc_root(inode)))
		goto iput_error;
	SPECFS_SB(sb) = sbi;
#ifdef HAVE_KMEMB_STRUCT_SUPER_BLOCK_S_D_OP
	sb->s_d_op = &spec_root_d_ops;
#endif
	return (0);
      iput_error:
	_ptrace(("inode %p no %lu refcount now %d\n", inode, inode->i_ino,
		 atomic_read(&inode->i_count) - 1));
	iput(inode);
      free_error:
	spec_sbi_free(sbi);
      error:
	return (err);
}

#ifdef HAVE_KMEMB_STRUCT_FILE_SYSTEM_TYPE_MOUNT
STATIC struct dentry *
specfs_fst_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
{
	_ptrace(("reading superblock\n"));
	return mount_single(fs_type, flags, data, specfs_fill_super);
}
STATIC void
specfs_kill_sb(struct super_block *sb)
{
	_ptrace(("killing superblock %p\n", sb));
#if 1
	return kill_anon_super(sb);
#else
#ifdef HAVE_KFUNC_KILL_LITTER_SUPER
	return kill_litter_super(sb);
#else
	return kill_anon_super(sb);
#endif
#endif
}

struct file_system_type spec_fs_type = {
	.owner = THIS_MODULE,
	.name = "specfs",
	.mount = specfs_fst_mount,
	.kill_sb = specfs_kill_sb,
};
#else
#ifdef HAVE_KMEMB_STRUCT_FILE_SYSTEM_TYPE_GET_SB
#ifdef HAVE_FILE_SYSTEM_TYPE_GET_SB_VFSMOUNT
STATIC int
specfs_get_sb(struct file_system_type *fs_type, int flags, const char *dev_name, void *data,
	      struct vfsmount *mnt)
{
	_ptrace(("reading superblock\n"));
	return get_sb_single(fs_type, flags, data, specfs_fill_super, mnt);
}
#else				/* HAVE_FILE_SYSTEM_TYPE_GET_SB_VFSMOUNT */
STATIC struct super_block *
specfs_get_sb(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
{
	_ptrace(("reading superblock\n"));
	return get_sb_single(fs_type, flags, data, specfs_fill_super);
}
#endif				/* HAVE_FILE_SYSTEM_TYPE_GET_SB_VFSMOUNT */
STATIC void
specfs_kill_sb(struct super_block *sb)
{
	_ptrace(("killing superblock %p\n", sb));
#if 1
	return kill_anon_super(sb);
#else
#ifdef HAVE_KFUNC_KILL_LITTER_SUPER
	return kill_litter_super(sb);
#else
	return kill_anon_super(sb);
#endif
#endif
}

struct file_system_type spec_fs_type = {
	.owner = THIS_MODULE,
	.name = "specfs",
	.get_sb = specfs_get_sb,
	.kill_sb = specfs_kill_sb,
};
#else
#ifdef HAVE_KMEMB_STRUCT_FILE_SYSTEM_TYPE_READ_SUPER
/**
 *  specfs_read_super: - create a shadow special filesystem super block
 *  @sb:	superblock for which to read a superblock inode
 *  @data:	options data
 *  @silent:	whether to ignore options errors
 *
 *  Create the super block inode.
 */
STATIC struct super_block *
specfs_read_super(struct super_block *sb, void *data, int silent)
{
	_ptrace(("reading superblock %p\n", sb));
	return (specfs_fill_super(sb, data, silent) ? NULL : sb);
}

STATIC DECLARE_FSTYPE(spec_fs_type, "specfs", specfs_read_super, FS_SINGLE);
#else
#error HAVE_KMEMB_STRUCT_FILE_SYSTEM_TYPE_GET_SB, HAVE_KMEMB_STRUCT_FILE_SYSTEM_TYPE_READ_SUPER or HAVE_KMEMB_STRUCT_FILE_SYSTEM_TYPE_MOUNT must be defined.
#endif
#endif
#endif

#if    defined DECLARE_MUTEX
STATIC DECLARE_MUTEX(specfs_sem);
#elif  defined DEFINE_SEMAPHORE
STATIC DEFINE_SEMAPHORE(specfs_sem);
#else
#error Need some way to declare a semaphore.
#endif
STATIC int specfs_count = 0;


streams_fastcall struct vfsmount *
specfs_mount(void)
{
	down(&specfs_sem);
	if (!specfs_mnt) {
		specfs_mnt = kern_mount(&spec_fs_type);
		if (IS_ERR(specfs_mnt))
			specfs_mnt = NULL;
	}
	if (specfs_mnt != NULL)
		specfs_count++;
	up(&specfs_sem);
	return (mntget(specfs_mnt));
}

EXPORT_SYMBOL_GPL(specfs_mount);

#if ! defined HAVE_KFUNC_KERN_UMOUNT
#undef kern_umount
#define kern_umount mntput
#endif

streams_fastcall void
specfs_umount(void)
{
	if (specfs_mnt) {
		mntput(specfs_mnt);
		down(&specfs_sem);
		if (specfs_mnt && specfs_count > 0)
			specfs_count--;
		if (specfs_count == 0 && specfs_mnt != NULL) {
			kern_umount(specfs_mnt);
			specfs_mnt = NULL;
		}
		up(&specfs_sem);
	}
}

EXPORT_SYMBOL_GPL(specfs_umount);

/**
 *  specfs_term_cache: - terminate the snode cache.
 */
static void
specfs_term_cache(void)
{
	if (snode_cachep != NULL) {
#ifdef HAVE_KTYPE_KMEM_CACHE_T_P
		if (kmem_cache_destroy(snode_cachep)) {
			printk(KERN_WARNING "%s: did not destroy snode_cachep\n", __FUNCTION__);
			return;
		}
#else				/* HAVE_KTYPE_KMEM_CACHE_T_P */
		kmem_cache_destroy(snode_cachep);
#endif				/* HAVE_KTYPE_KMEM_CACHE_T_P */
		printk(KERN_DEBUG "%s: destroyed snode cache\n", __FUNCTION__);
		snode_cachep = NULL;
	}
	return;
}

static void
#if !defined(HAVE_KFUNC_KMEM_CACHE_CREATE_5_ARGS) && \
    !defined(HAVE_KFUNC_KMEM_CACHE_CREATE_5_NEW)
snode_init_once(void *data, kmem_cachep_t cachep, unsigned long flags)
#elif defined(HAVE_KFUNC_KMEM_CACHE_CREATE_5_ARGS)
snode_init_once(kmem_cachep_t cachep, void *data)
#elif defined(HAVE_KFUNC_KMEM_CACHE_CREATE_5_NEW)
snode_init_once(void *data)
#endif
{
	struct inode *inode = (struct inode *) data;

#if defined SLAB_CTOR_VERIFY && defined SLAB_CTOR_CONSTRUCTOR
	if ((flags & (SLAB_CTOR_VERIFY | SLAB_CTOR_CONSTRUCTOR)) == SLAB_CTOR_CONSTRUCTOR)
#endif
		inode_init_once(inode);
}

/**
 *  specfs_init_cache: - initialize the snode cache.
 */
static int
specfs_init_cache(void)
{
	if (snode_cachep == NULL) {
		snode_cachep = kmem_create_cache("snode_cache", sizeof(struct inode), 0,
						 SLAB_HWCACHE_ALIGN, snode_init_once, NULL);
		if (snode_cachep == NULL) {
			printk(KERN_WARNING "%s: Cannot allocate snode_cache\n", __FUNCTION__);
			return (-ENOMEM);
		}
		printk(KERN_DEBUG "%s: initialized snode cache\n", __FUNCTION__);
	}
	return (0);
}

/**
 *  strspecfs_init: - initialize the shadow special filesystem
 */
#ifdef CONFIG_STREAMS_MODULE
static
#endif
int __init
specfs_init(void)
{
	int result;

#ifdef CONFIG_STREAMS_MODULE
	printk(KERN_INFO SPECFS_BANNER);	/* log message */
#else
	printk(KERN_INFO SPECFS_SPLASH);	/* console splash */
#endif
	if ((result = strlock_init()))
		goto no_locks;
	if ((result = specfs_init_cache()))
		goto no_cache;
	if ((result = register_filesystem(&spec_fs_type)))
		goto no_specfs;
	if ((result = strlookup_init()))
		goto no_lookup;
	return (0);
      no_lookup:
	unregister_filesystem(&spec_fs_type);
      no_specfs:
	specfs_term_cache();
      no_cache:
	strlock_exit();
      no_locks:
	return (result);
}

/**
 *  strspecfs_exit: - deinitialize the shadow special filesystem
 */
#ifdef CONFIG_STREAMS_MODULE
static
#endif
void __exit
specfs_exit(void)
{
	strlookup_exit();
	unregister_filesystem(&spec_fs_type);
	specfs_term_cache();
	strlock_exit();
}

#ifdef CONFIG_STREAMS_MODULE
module_init(specfs_init);
module_exit(specfs_exit);
#endif
