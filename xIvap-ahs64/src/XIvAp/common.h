/***************************************************************************
 *   Copyright (C) 2006 by Martin Domig                                    *
 *   martin@domig.net                                                      *
 *                                                                         *
 *   For license information see LICENSE.xivap in the root folder of the   *
 *   source code.                                                          *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 ***************************************************************************/

#ifndef COMMON_H_
#define COMMON_H_

#include <map>
#include <vector>
#include <string>

#ifndef WIN32
#include <inttypes.h>
#endif

// define some basic types
typedef unsigned char  UInt8;
typedef unsigned short UInt16;

#ifdef APPLE
    #if (X64)
    typedef  unsigned int UInt32;
    #else
    typedef long unsigned int UInt32;
    #endif
#else
typedef unsigned int   UInt32;
#endif

#include "ptypes.h"
#include "pasync.h"
#include "pinet.h"
#include "pport.h"
#include "pstreams.h"
#include "ptime.h"

USING_PTYPES

#include <stdio.h>
#include <string.h>
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMMenus.h"
#include "XPLMNavigation.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"
#include "XPUIGraphics.h"
#include "XPLMPlugin.h"

#include "ptpos.h"

#if 0
#undef ntohl
#undef ntohs
#undef htonl
#undef htons
#endif

#ifndef WIN32
inline float htonf( const float f )
{
    int i = htonl( *(int *)&f );
    return *(float *)&i;
}

inline float ntohf1( const float f )
{
    int i = ntohl( *(int *)&f );
    return *(float *)&i;
}
#endif

// macro to convert a pt::string to std::string
#define STDSTRING(s) std::string(pconst(s))

// defines

#define _FSD_POLL_INTERVAL_			0.2f

#define SOFTWARE_NAME		"X-IvAp AHS"
#include "version.h"

//splitted the copyrightlines to fit in the resized window 18/08/2012
#define SOFTWARE_COPYRIGHT1	"(c)2005-2013 by Martin Domig, Kristof Provost, Andrew McGregor"
#define	SOFTWARE_COPYRIGHT2	"Thijmen de Gooijer, Kenny Moens, X-AiR Team, XFMC Team"
#define	SOFTWARE_COPYRIGHT3	"AHS version (c) 2014 by Mikel N'Dong (AHS120D)"
#define SOFTWARE_COPYRIGHT4 "Tomas Garcia Fresno (AHS232D)"
#define SOFTWARE_COPYRIGHT5 "Jose Manuel Garcia Valladolid (AHS018D)"

#ifdef IVAO
#define UNICOM_NAME       "UNICOM"
#define UNICOM_FREQ       "122.800"
#define UNICOM_FREQ_NUM   12280
#define UNICOM_DIST       120
#else

//#define UNICOM_NAME		"AIR-AIR"
//#define UNICOM_FREQ		"123.450"
//#define UNICOM_FREQ_NUM		12345

#define AHS_SERVER_URL "95.211.55.201/"
#define UNICOM_NAME		"UNICOM"
#define UNICOM_FREQ		"122.800"
#define UNICOM_FREQ_NUM		12280
#define UNICOM_DIST		120
#define TS_CANAL_GENERAL "LA CANTINA DEL PILOTO"
#endif

#define PLUGIN_DIR "X-IvAp AHS" // A�adido para conversi�n a "Fat plugin"
#define RESOURCES_DIR	"X-IvAp AHS Resources"
#define CONFIG_FILE		"X-IvAp AHS.conf"
#define STATIONS_FILE	"icao.dat"

#define FLIGHTPLANS_DIR	"Flightplans"
#define DEFAULT_FPL		"Default.fpl"

#define SERVERSTATUS_URL "http://www.ivao.aero/network/status.asp"
#define SERVERS_FILENAME "serverlist.txt"
#define OWN_SERVERS_FILENAME "myservers.txt"

#define AHSCONTROL_IP "95.211.55.201"
#define AHSCONTROL_RES "http://www.airhispania.com/modact01.php?tCod=mod_actahs"
#define AHSCONTROL_FILE "ahsStatus.html"

// p2p settings

#define P2P_POS_PROTOCOL "PPOS1"

// will ping peers this often
#define P2P_PING_INTERVAL 3000000

// send keepalive to stun server this often
#define P2P_KEEPALIVE_INTERVAL 30000000

// interval (seconds) at which we re-calculate peer pos. frequencies
#define P2P_FREQUENCY_INTERVAL 5.0f

// atc positions become invalid after being dead for this time
#define ATCPOS_MAX_AGE 60.0f

// weather will be discarded after being dead for this time
#define WEATHER_MAX_AGE 60.f * 60.f  // 1h

// check for new weather stations this often
#define WEATHER_UPDATE_INTERVAL 30.0f

// use GLOB weather if the nearest wx station is more than this many nm away
#define WEATHER_GLOB_TRESHOLD 60.0f

// if we are flying between 2 weather stations, switch to the closest station
// only if the difference in distance to the current station is greater than this
#define WEATHER_SWITCH_HYSTERESE 3

// FIXME: Salida de debug para el tiempo
//#define WX_DEBUG

#define SELCAL_BEEP_1 400
#define SELCAL_BEEP_2 1300

class Xivap;
extern Xivap xivap;

extern float colWhite[];
extern float colLightGray[];
extern float colBlue[];
extern float colLightBlue[];
extern float colRed[];
extern float colGreen[];
extern float colDarkGreen[];
extern float colYellow[];
extern float colCyan[];
extern float colGray[];


#ifdef WIN32
#define PLATFORM "Windows"
#define FSD_SOFTWARE_NAME "X-IvAp/win AHS"

#pragma warning ( disable : 4311 )

#endif

#ifdef LINUX
#define PLATFORM "Linux"
#define FSD_SOFTWARE_NAME "X-IvAp/lin AHS"
#endif

#ifdef APPLE
#define PLATFORM "Mac"
#define FSD_SOFTWARE_NAME "X-IvAp/mac AHS"
#endif

/*
// Niveles de debuging para el comando "DEBUG"
#ifndef DEBUGLEVELS
#define DEBUGLEVELS
	union Debuglevels {
		unsigned int debuglevels;
		struct {
			unsigned int net				: 1;
			unsigned int weather			: 2;
			unsigned int multiplayer		: 1;
			unsigned int teamspeak			: 1;
			unsigned int params				: 1;
			unsigned int ui					: 1;
	
			unsigned int unused				: 25;

		};
	};
#endif
extern Debuglevels debug;
*/

// uncomment this line to compile a private beta
// #define INTERNAL_BETA

// comment this to compile a public release
// #define BETA

#define EXPIRE_YEAR		2012
#define EXPIRE_MONTH	12
#define EXPIRE_DAY		31

#ifdef INTERNAL_BETA
// warn on release builds
#ifndef BETA
#define BETA
#endif
#pragma message( "WARNING - INTERNAL BETA BUILD --------------------" )
#else
#ifdef BETA
#pragma message( "WARNING - BETA BUILD -------" )
#endif


#endif

#endif // header
