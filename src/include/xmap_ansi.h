/*****************************************************************************

 @(#) $Id: xmap_ansi.h,v 1.1.2.2 2010-11-28 14:21:44 brian Exp $

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2010  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation; version 3 of the License.

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

 Last Modified $Date: 2010-11-28 14:21:44 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: xmap_ansi.h,v $
 Revision 1.1.2.2  2010-11-28 14:21:44  brian
 - remove #ident, protect _XOPEN_SOURCE

 Revision 1.1.2.1  2009-06-21 11:23:46  brian
 - added files to new distro

 *****************************************************************************/

#ifndef __XMAP_ANSI_H__
#define __XMAP_ANSI_H__

typedef enum {
	MAP_T_AUTHENTICATION_DIRECTIVE = 27,
	MAP_T_AUTHENTICATION_DIRECTIVE_FORWARD = 39,
	MAP_T_AUTHENTICATION_FAILURE_REPORT = 30,
	MAP_T_AUTHENTICATION_REQUEST = 28,
	MAP_T_AUTHENTICATION_STATUS_REPORT = 40,
	MAP_T_BASE_STATION_CHALLENGE = 29,
	MAP_T_BLOCKING = 8,
	MAP_T_BULK_DEREGISTRATION = 34,
	MAP_T_COUNT_REQUEST = 31,
	MAP_T_FACILITIES_DIRECTIVE = 2,
	MAP_T_FACILITIES_DIRECTIVE_2 = 36,
	MAP_T_FACILITIES_RELEASE = 5,
	MAP_T_FEATURE_REQUEST = 17,
	MAP_T_FLASH_REQUEST = 26,
	MAP_T_HANDOFF_BACK_2 = 37,
	MAP_T_HANDOFF_BACK = 4,
	MAP_T_HANDOFF_MEASUREMENT_REQUEST = 1,
	MAP_T_HANDOFF_MEASUREMENT_REQUEST_2 = 35,
	MAP_T_HANDOFF_TO_THIRD_2 = 38,
	MAP_T_HANDOFF_TO_THIRD = 25,
	MAP_T_INFORMATION_DIRECTIVE = 42,
	MAP_T_INFORMATION_FORWARD = 43,
	MAP_T_INTER_SYSTEM_ANSWER = 44,
	MAP_T_INTER_SYSTEM_PAGE_2 = 45,
	MAP_T_INTER_SYSTEM_PAGE = 32,
	MAP_T_INTER_SYSTEM_SETUP = 46,
	MAP_T_LOCATION_REQUEST = 15,
	MAP_T_MOBILE_ON_CHANNEL = 3,
	MAP_T_MS_INACTIVE = 22,
	MAP_T_ORIGINATION_REQUEST = 47,
	MAP_T_QUALIFICATION_DIRECTIVE = 7,
	MAP_T_QUALIFICATION_REQUEST = 6,
	MAP_T_RANDOM_VARIABLE_REQUEST = 48,
	MAP_T_REDIRECTION_DIRECTIVE = 49,
	MAP_T_REDIRECTION_REQUEST = 24,
	MAP_T_REGISTRATION_CANCELLATION = 14,
	MAP_T_REGISTRATION_NOTIFICATION = 13,
	MAP_T_REMOTE_USER_INTERACTION_DIRECTIVE = 50,
	MAP_T_RESET_CIRCUIT = 10,
	MAP_T_ROUTING_REQUEST = 16,
	MAP_T_SMS_DELIVERY_BACKWARD = 51,
	MAP_T_SMS_DELIVERY_FORWARD = 52,
	MAP_T_SMS_DELIVERY_POINT_TO_POINT = 53,
	MAP_T_SMS_NOTIFICATION = 54,
	MAP_T_SMS_REQUEST = 55,
	MAP_T_TRANSFER_TO_NUMBER_REQUEST = 23,
	MAP_T_TRUNK_TEST = 11,
	MAP_T_TRUNK_TEST_DISCONNECT = 12,
	MAP_T_UNBLOCKING = 9,
	MAP_T_UNRELIABLE_ROAMER_DATA_DIRECTIVE = 20,
	MAP_T_UNSOLICITED_RESPONSE = 33,
} MAP_T_Operation_Code;

typedef enum {
	MAP_T_BILLING_ID = 1,
	MAP_T_SERVING_CELL_ID = 2,
	MAP_T_TARGET_CELL_ID = 3,
	MAP_T_DIGITS = 4,
	MAP_T_CHANNEL_DATA = 5,
	MAP_T_INTER_MSC_CIRCUIT_ID = 6,
	MAP_T_INTER_SWITCH_COUNT = 7,
	MAP_T_MOBILE_IDENTIFICATION_NUMBER = 8,
	MAP_T_ELECTRONIC_SERIAL_NUMBER = 9,
	MAP_T_RELEASE_REASON = 10,
	MAP_T_SIGNAL_QUALITY = 11,
	MAP_T_STATION_CLASS_MARK = 12,
	MAP_T_AUTHORIZATION_DENIED = 13,
	MAP_T_AUTHORIZATION_PERIOD = 14,
	MAP_T_SEIZURE_TYPE = 15,
	MAP_T_TRUNK_STATUS = 16,
	MAP_T_QUALIFICATION_INFORMATION_CODE = 17,
	MAP_T_FEATURE_RESULT = 18,
	MAP_T_REDIRECTION_REASON = 19,
	MAP_T_ACCESS_DENIED_REASON = 20,
	MAP_T_MSCID = 21,
	MAP_T_SYSTEM_MY_TYPE_CODE = 22,
	MAP_T_ORIGINATION_INDICATOR = 23,
	MAP_T_TERMINATION_RESTRICTION_CODE = 24,
	MAP_T_CALLING_FEATURES_INDICATOR = 25,
	MAP_T_FAULTY_PARAMETER = 26,
	MAP_T_TDMA_CHANNEL_DATA = 28,
	MAP_T_TDMA_CALL_MODE = 29,
	MAP_T_HANDOFF_REASON = 30,
	MAP_T_TDMA_BURST_INDICATOR = 31,
	MAP_T_PC_SSN = 32,
	MAP_T_LOCATION_AREA_ID = 33,
	MAP_T_SYSTEM_ACCESS_TYPE = 34,
	MAP_T_AUTHENTICATION_RESPONSE = 35,
	MAP_T_AUTHENTICATION_RESPONSE_BASE_STATION = 36,
	MAP_T_AUTHENTICATION_RESPONSE_UNIQUE_CHALLENGE = 37,
	MAP_T_CALL_HISTORY = 38,
	MAP_T_CONFIDENTIALITY_MODES = 39,
	MAP_T_RANDOM_VARIABLE = 40,
	MAP_T_RANDOM_VARIABLE_BASE_STATION = 41,
	MAP_T_RANDOM_VARIABLE_SSD = 42,
	MAP_T_RANDOM_VARIABLE_UNIQUE_CHALLENGE = 43,
	MAP_T_REPORT_TYPE = 44,
	MAP_T_SIGNALING_MESSAGE_ENCRYPTION_KEY = 45,
	MAP_T_SHARED_SECRET_DATA = 46,
	MAP_T_TERMINAL_TYPE = 47,
	MAP_T_VOICE_PRIVACY_MASK = 48,
	MAP_T_SYSTEM_CAPABILITIES = 49,
	MAP_T_DENY_ACCESS = 50,
	MAP_T_UPDATE_COUNT = 51,
	MAP_T_SSD_NOT_SHARED = 52,
	MAP_T_EXTENDED_MSCID = 53,
	MAP_T_EXTENDED_SYSTEM_MY_TYPE_CODE = 54,
	MAP_T_CONTROL_CHANNEL_DATA = 55,
	MAP_T_SYSTEM_ACCESS_DATA = 56,
	MAP_T_CANCELLATION_DENIED = 57,
	MAP_T_BORDER_CELL_ACCESS = 58,
	MAP_T_CDMA_STATION_CLASS_MARK = 59,
	MAP_T_CDMA_SERVING_ONE_WAY_DELAY = 60,
	MAP_T_CDMA_TARGET_ONE_WAY_DELAY = 61,
	MAP_T_CDMA_CALL_MODE = 62,
	MAP_T_CDMA_CHANNEL_DATA = 63,
	MAP_T_CDMA_SIGNAL_QUALITY = 64,
	MAP_T_CDMA_PILOT_STRENGTH = 65,
	MAP_T_CDMA_MOBILE_PROTOCOL_REVISION = 66,
	MAP_T_CDMA_PRIVATE_LONG_CODE_MASK = 67,
	MAP_T_CDMA_CODE_CHANNEL = 68,
	MAP_T_CDMA_SEARCH_WINDOW = 69,
	MAP_T_MS_LOCATION = 70,
	MAP_T_PAGE_INDICATOR = 71,
	MAP_T_RECEIVED_SIGNAL_QUALITY = 72,
	MAP_T_DEREGISTRATION_TYPE = 73,
	MAP_T_NAMPS_CHANNEL_DATA = 74,
	MAP_T_ALERT_CODE = 75,
	MAP_T_ANNOUNCEMENT_CODE = 76,
	MAP_T_AUTHENTICATION_ALGORITHM_VERSION = 77,
	MAP_T_AUTHENTICATION_CAPABILITY = 78,
	MAP_T_CALL_HISTORY_COUNT_EXPECTED = 79,
	MAP_T_CALLING_PARTY_NUMBER_DIGITS_1 = 80,
	MAP_T_CALLING_PARTY_NUMBER_DIGITS_2 = 81,
	MAP_T_CALLING_PARTY_NUMBER_STRING_1 = 82,
	MAP_T_CALLING_PARTY_NUMBER_STRING_2 = 83,
	MAP_T_CALLING_PARTY_SUBADDRESS = 84,
	MAP_T_CANCELLATION_TYPE = 85,
	MAP_T_CARRIER_DIGITS = 86,
	MAP_T_DESTINATION_DIGITS = 87,
	MAP_T_DMH_REDIRECTION_INDICATOR = 88,
	MAP_T_INTERSYSTEM_TERMINATION = 89,
	MAP_T_AVAILABILITY_TYPE = 90,
	MAP_T_LOCAL_TERMINATION = 91,
	MAP_T_MESSAGE_WAITING_NOTIFICATION_COUNT = 92,
	MAP_T_MOBILE_DIRECTORY_NUMBER = 93,
	MAP_T_MSC_IDENTIFICATION_NUMBER = 94,
	MAP_T_PSTN_TERMINATION = 95,
	MAP_T_NO_ANSWER_TIME = 96,
	MAP_T_ONE_TIME_FEATURE_INDICATOR = 97,
	MAP_T_ORIGINATION_TRIGGERS = 98,
	MAP_T_RANDC = 99,
	MAP_T_REDIRECTING_NUMBER_DIGITS = 100,
	MAP_T_REDIRECTING_NUMBER_STRING = 101,
	MAP_T_REDIRECTING_SUBADDRESS = 102,
	MAP_T_SENDER_IDENTIFICATION_NUMBER = 103,
	MAP_T_SMS_ADDRESS = 104,
	MAP_T_SMS_BEARER_DATA = 105,
	MAP_T_SMS_CHARGE_INDICATOR = 106,
	MAP_T_SMS_DESTINATION_ADDRESS = 107,
	MAP_T_SMS_MESSAGE_COUNT = 108,
	MAP_T_SMS_NOTIFICATION_INDICATOR = 109,
	MAP_T_SMS_ORIGINAL_DESTINATION_ADDRESS = 110,
	MAP_T_SMS_ORIGINAL_DESTINATION_SUBADDRESS = 111,
	MAP_T_SMS_ORIGINAL_ORIGINATING_ADDRESS = 112,
	MAP_T_SMS_ORIGINAL_ORIGINATING_SUBADDRESS = 113,
	MAP_T_SMS_ORIGINATING_ADDRESS = 114,
	MAP_T_SMS_ORIGINATION_RESTRICTIONS = 115,
	MAP_T_SMS_TELESERVICE_IDENTIFIER = 116,
	MAP_T_SMS_TERMINATION_RESTRICTIONS = 117,
	MAP_T_SMS_MESSAGE_WAITING_INDICATOR = 118,
	MAP_T_TERMINATION_ACCESS_TYPE = 119,
	MAP_T_TERMINATION_LIST = 120,
	MAP_T_TERMINATION_TREATMENT = 121,
	MAP_T_TERMINATION_TRIGGERS = 122,
	MAP_T_TRANSACTION_CAPABILITY = 123,
	MAP_T_UNIQUE_CHALLENGE_REPORT = 124,
	MAP_T_ACTION_CODE = 128,
	MAP_T_ALERT_RESULT = 129,
	MAP_T_ANNOUNCEMENT_LIST = 130,
	MAP_T_CDMA_CODE_CHANNEL_INFORMATION = 131,
	MAP_T_CDMA_CODE_CHANNEL_LIST = 132,
	MAP_T_CDMA_TARGET_MEASUREMENT_INFORMATION = 133,
	MAP_T_CDMA_TARGET_MEASUREMENT_LIST = 134,
	MAP_T_CDMA_TARGET_MAHO_INFORMATION = 135,
	MAP_T_CDMA_TARGET_MAHO_LIST = 136,
	MAP_T_CONFERENCE_CALLING_INDICATOR = 137,
	MAP_T_COUNT_UPDATE_REPORT = 138,
	MAP_T_DIGIT_COLLECTION_CONTROL = 139,
	MAP_T_DHM_ACCOUNT_CODE_DIGITS = 140,
	MAP_T_DHM_ALTERNATE_BILLING_DIGITS = 141,
	MAP_T_DHM_BILLING_DIGITS = 142,
	MAP_T_GEOGRAPHIC_AUTHORIZATION = 143,
	MAP_T_LEG_INFORMATION = 144,
	MAP_T_MESSAGE_WAITING_NOTIFICATION_TYPE = 145,
	MAP_T_PACA_INDICATOR = 146,
	MAP_T_PREFERRED_LANGUAGE_INDICATOR = 147,
	MAP_T_RAND_VALID_TIME = 148,
	MAP_T_RESTRICTION_DIGITS = 149,
	MAP_T_ROUTING_DIGITS = 150,
	MAP_T_SETUP_RESULT = 151,
	MAP_T_SMS_ACCESS_DENIED_REASON = 152,
	MAP_T_SMS_CAUSE_CODE = 153,
	MAP_T_SPINI_PIN = 154,
	MAP_T_SPINI_TRIGGERS = 155,
	MAP_T_SSD_UPDATE_REPORT = 156,
	MAP_T_TARGET_MEASUREMENT_INFORMATION = 157,
	MAP_T_TARGET_MEASUREMENT_LIST = 158,
	MAP_T_VOICE_MAILBOX_PIN = 159,
	MAP_T_VOICE_MAILBOX_NUMBER = 160,
	MAP_T_AUTHENTICATION_DATA = 161,
	MAP_T_CONDITIONALLY_DENIED_REASON = 162,
	MAP_T_GROUP_INFORMATION = 163,
	MAP_T_HANDOFF_STATE = 164,
	MAP_T_NAMPS_CALL_MODE = 165,
	MAP_T_CDMA_SLOT_CYCLE_INDEX = 166,
	MAP_T_DENIED_AUTHORIZATION_PERIOD = 167,
	MAP_T_PILOT_NUMBER = 168,
	MAP_T_PILOT_BILLING_ID = 169,
} MAP_T_Parameter_Code;

#endif				/* __XMAP_ANSI_H__ */

