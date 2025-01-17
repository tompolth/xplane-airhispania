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

#include "fsdapi.h"
#include "helpers.h"
#include "xivap.h"
#include "configFile.h"

#define FSDAPI_DUMP_COMMUNICATION
//#define IVAO

Flightplan::Flightplan():
	flightrules(""), aircrafttype(""), cruisespeed(""), departure(""), deptimeest(""),
	deptimeact(""), cruisealt(""), destination(""), hoursenroute(""), minenroute(""),
	hoursfuel(""), minfuel(""), alternate(""), remarks(""), route(""), _errorMessage(""),
	typeofflight(""), pob(""), alternate2(""), number(""), wtc(""), equip(""), transpondertype(""),
	fmcroute(""), alttype(""), speedtype(""), airline(""), livery(""), pic(""), callsign("")
{
}

void Flightplan::save(string filename)
{
	ConfigFile fpl;
	fpl.setConfig("FLIGHTPLAN", "RULES", flightrules);
	fpl.setConfig("FLIGHTPLAN", "FLIGHTTYPE", typeofflight);
	fpl.setConfig("FLIGHTPLAN", "NUMBER", number);
	fpl.setConfig("FLIGHTPLAN", "ACTYPE", aircrafttype);
	fpl.setConfig("FLIGHTPLAN", "WAKECAT", wtc);
	fpl.setConfig("FLIGHTPLAN", "EQUIPMENT", equip);
	fpl.setConfig("FLIGHTPLAN", "TRANSPONDER", transpondertype);
	fpl.setConfig("FLIGHTPLAN", "DEPICAO", departure);
	fpl.setConfig("FLIGHTPLAN", "DEPTIME", deptimeest);
	fpl.setConfig("FLIGHTPLAN", "SPEED", cruisespeed);
	fpl.setConfig("FLIGHTPLAN", "LEVELTYPE", alttype);
	fpl.setConfig("FLIGHTPLAN", "LEVEL", cruisealt);
	fpl.setConfig("FLIGHTPLAN", "ROUTE", route);
	fpl.setConfig("FLIGHTPLAN", "DESTICAO", destination);
	fpl.setConfig("FLIGHTPLAN", "EET", hoursenroute + minenroute);
	fpl.setConfig("FLIGHTPLAN", "ALTICAO", alternate);
	fpl.setConfig("FLIGHTPLAN", "ALT2ICAO", alternate2);
	fpl.setConfig("FLIGHTPLAN", "OTHER", remarks);
	fpl.setConfig("FLIGHTPLAN", "ENDURANCE", hoursfuel + minfuel);
	fpl.setConfig("FLIGHTPLAN", "POB", pob);
	fpl.setConfig("FLIGHTPLAN", "SPEEDTYPE",  speedtype);
	fpl.setConfig("FLIGHTPLAN", "AIRLINE",  airline);
	fpl.setConfig("FLIGHTPLAN", "LIVERY",  livery);
	fpl.setConfig("FLIGHTPLAN", "FMCROUTE",  fmcroute);
	fpl.setConfig("FLIGHTPLAN", "PIC",  pic);
	fpl.setConfig("FLIGHTPLAN", "CALLSIGN",  callsign);
	fpl.save(filename);
}

void Flightplan::load(string filename)
{
	ConfigFile fpl;
	fpl.load(filename);
	flightrules = fpl.readConfig("FLIGHTPLAN", "RULES");
	typeofflight = fpl.readConfig("FLIGHTPLAN", "FLIGHTTYPE");
	number = fpl.readConfig("FLIGHTPLAN", "NUMBER");
	aircrafttype = fpl.readConfig("FLIGHTPLAN", "ACTYPE");
	wtc = fpl.readConfig("FLIGHTPLAN", "WAKECAT");
	equip = fpl.readConfig("FLIGHTPLAN", "EQUIPMENT");
	transpondertype = fpl.readConfig("FLIGHTPLAN", "TRANSPONDER");
	departure = fpl.readConfig("FLIGHTPLAN", "DEPICAO");
	deptimeest = fpl.readConfig("FLIGHTPLAN", "DEPTIME");
	cruisespeed = fpl.readConfig("FLIGHTPLAN", "SPEED");
	alttype = fpl.readConfig("FLIGHTPLAN", "LEVELTYPE");
	cruisealt = fpl.readConfig("FLIGHTPLAN", "LEVEL");
	route = fpl.readConfig("FLIGHTPLAN", "ROUTE");
	destination = fpl.readConfig("FLIGHTPLAN", "DESTICAO");

	hoursenroute = fpl.readConfig("FLIGHTPLAN", "EET");
	while(length(hoursenroute) < 4) hoursenroute = "0" + hoursenroute;
	minenroute = copy(hoursenroute, 2, 2);
	del(hoursenroute, 2, 2);

	alternate = fpl.readConfig("FLIGHTPLAN", "ALTICAO");
	alternate2 = fpl.readConfig("FLIGHTPLAN", "ALT2ICAO");
	remarks = fpl.readConfig("FLIGHTPLAN", "OTHER");

	hoursfuel = fpl.readConfig("FLIGHTPLAN", "ENDURANCE");
	while(length(hoursfuel) < 4) hoursfuel = "0" + hoursfuel;
	minfuel = copy(hoursfuel, 2, 2);
	del(hoursfuel, 2, 2);

	pob = fpl.readConfig("FLIGHTPLAN", "POB");
	speedtype = fpl.readConfig("FLIGHTPLAN", "SPEEDTYPE");
	airline = fpl.readConfig("FLIGHTPLAN", "AIRLINE");
	livery = fpl.readConfig("FLIGHTPLAN", "LIVERY");
	fmcroute = fpl.readConfig("FLIGHTPLAN", "FMCROUTE");
	pic = fpl.readConfig("FLIGHTPLAN", "PIC");
	callsign = fpl.readConfig("FLIGHTPLAN", "CALLSIGN");
}

void Flightplan::normalize()
{
	while(length(deptimeest) < 4) deptimeest = "0" + deptimeest;
	while(length(deptimeact) < 4) deptimeact = "0" + deptimeact;
	while(length(hoursenroute) < 2) hoursenroute = "0" + hoursenroute;
	while(length(minenroute) < 2) minenroute = "0" + minenroute;
	while(length(hoursfuel) < 2) hoursfuel = "0" + hoursfuel;
	while(length(minfuel) < 2) minfuel = "0" + minfuel;
	departure = strupcase(trim(departure));
	destination = strupcase(trim(destination));
	alternate = strupcase(trim(alternate));
	alternate2 = strupcase(trim(alternate2));
	route = strupcase(trim(route));
	if(stringtoi(pob) < 0) pob = "1";
	if(stringtoi(number) < 0) number = "1";

	aircrafttype = strupcase(aircrafttype);
	typeofflight = strupcase(typeofflight);
	flightrules = strupcase(flightrules);
	alttype = strupcase(alttype);
	wtc = strupcase(wtc);
}

string Flightplan::aircraft()
{
	return number + "/" + aircrafttype + "/" + wtc + "-" + equip + "/" + transpondertype; // Recuperado del original, por si acaso, pero no se utiliza para enviar el PV
//	return "T/" + aircrafttype + "/G"; // FIXME: Sacar de alguna parte las equivalencias "T,H,B,L,0..." y "F,G,R,A,..."
}

#define FPCHECK(b, m) { if(b) { _errorMessage = string(m); return false; } }
#define FPCHECKST(s, c, m) { if(pos(s, c) < 0) { _errorMessage = string(m); return false; } }

bool Flightplan::isValid()
{
	normalize();

	FPCHECK(length(aircrafttype) < 2, "Aircraft type is invalid");
	FPCHECK(length(aircrafttype) > 4, "Aircraft type is invalid");

	if(length(airline) > 0) {
		FPCHECK(length(airline) != 3, "Airline code is invalid");
	}

	FPCHECK(length(typeofflight) != 1, "invalid flight type '" + typeofflight + "'");
	FPCHECKST(typeofflight, "SNGMX", "flight type must be one of S,N,G,M,X");

	FPCHECK(length(flightrules) != 1, "invalid flight rule '" + flightrules + "'");
	FPCHECKST(flightrules, "IVYZ", "flight rule must be one of I,V,Y,Z");

	FPCHECK(length(speedtype) != 1, "invalid speed type '" + speedtype + "'");
	FPCHECKST(speedtype, "NM", "flight rule must be one of N,M");

	FPCHECK(length(cruisespeed) < 2, "invalid cruise speed");
	FPCHECK(stringtoi(cruisespeed) <= 0, cruisespeed + " is not a valid number");

	FPCHECK(length(wtc) != 1, "invalid WTC '" + flightrules + "'");
	FPCHECKST(wtc, "LMH", "WTC must be one of L,M,H");

	FPCHECK(length(departure) < 3, "invalid departure airport");
	FPCHECK(length(deptimeest) != 4, "invalid estimated departure time");
	FPCHECK(length(deptimeact) > 4, "invalid actual departure time");

	if(alttype == "VFR") cruisealt = "0";
	else {
		FPCHECK(length(alttype) != 1, "invalid altitude type");
		FPCHECKST(alttype, "FA", "flight rule must be one of F,A");
		FPCHECK(stringtoi(cruisealt) <= 0, cruisealt + " is not a valid number");
	}

	FPCHECK(length(destination) < 3, "invalid destination airport");
	FPCHECK(length(hoursenroute) != 2, "invalid hours en route");
	FPCHECK(length(minenroute) != 2, "invalid minutes en route");
	FPCHECK(length(hoursfuel) != 2, "invalid fuel hours");
	FPCHECK(length(minfuel) != 2, "invalid fuel minutes");
	FPCHECK(length(alternate) > 4, "invalid alternate airport");
	FPCHECK(length(alternate2) > 4, "invalid 2nd alternate airport");
	FPCHECK(length(remarks) > 100, "remarks field is too long");
	FPCHECK(length(route) > 384, "route field is too long");
	_errorMessage = "";
	return true;
}

FsdAPI::FsdAPI()
{

	_connected = false;
#ifndef IVAO                                                                                                                      
        _verified = true;                                                                                                          
#endif  
	_realname = _id = _callsign = _host = _mypublicip = _password = "";
	_rating = -1;
	_admin = FSD::ADM_USER;
	_params.params = 0;
	_sendSubscribeWX = false;
	_sendPlaneInfo = false;
	_sendVoice = false;
	_mtl = "";
	_usingWX = false;
	_usingVoice = false;
	_loadMTLAliases();
}

void FsdAPI::_loadMTLAliases()
{
	// load the MTL alias list
	string filename = getXivapRessourcesDir() + "mtlalias.txt";

	char l[512];
	int linesize = 511;

    FILE *in = fopen(pconst(filename), "r");

	_cslAliases.clear();
    if(in == NULL) return;

	string line = "";
	std::pair<std::string, std::string> entry;
	do {
		fgets(l, linesize, in);
		l[linesize] = 0;
		if(feof(in)) line = "";
		else {
			line = l;
			line = strupcase(trim(line));

			if(length(line) > 0) {
				if(line[0] != '"') continue;

				del(line, 0, 1);
				// DHLRSTRP" "DHLOLD"
				int p = pos('"', line); if(p < 0) continue;
				entry.first = pconst(copy(line, 0, p));
				del(line, 0, p+1);
				line = trim(line);

				// "DHLOLD"
				if(line[0] != '"') continue;
				del(line, 0, 1);

				// DHLOLD"
				p = pos('"', line); if(p < 0) continue;
				entry.second = pconst(copy(line, 0, p));

				// MTL -> CSL
				_cslAliases[entry.second] = entry.first;
			}
		}
	} while(!feof(in));
	fclose(in);
}

void FsdAPI::connectPilot(string host, string port, string callsign, string id, string password,
		bool hideadm, FSD::SimulatorType sim, string realname)
{

	// refuse to connect a pilot without knowing plane information
	if(_mtl == "" || !_sendPlaneInfo)
		return;

	_socket.open(host, port);
	_connected = true;
	callsign = trim(strupcase(callsign));

	// source dest vid pass rating/hideadm revision simulator realname
	// #APN1697J:SERVER:VID:PASSWORD:1:B:1:Joe Blow
	// Modificado para red AHS:
	// #APAHSnnnx:SERVER:USUARIO:CLAVE:1:9:1:Nombre Apellido
	FSD::Message packet;
	packet.type = _FSD_ADDPILOT_;
	packet.source = callsign;
	packet.dest = _FSD_SERVERDEST_;
	packet.tokens.push_back("AHS"+id);
	packet.tokens.push_back(password);
//	packet.tokens.push_back(hideadm ? "1" : "11"); // FIXME: Si da problemas, dejarlo a "1" siempre (LOS DA)
	packet.tokens.push_back("1");
	packet.tokens.push_back(_FSD_REVISION_);
//	packet.tokens.push_back("9");
	packet.tokens.push_back(itostring(sim));
	packet.tokens.push_back(realname);
	send(packet);

	_callsign = callsign;
	_password = password;
	_id = id;
	_host = host + ":" + port;
	_connectHost = host;
	_connectPort = atoi(port);
	_realname = realname;
}


FSD::Message FsdAPI::receive()
{
	FSD::Message m;

	if(!_connected) return m;

	if(!_socket.connected()) {
		_connected = false;
		if(length(_socket.errorMessage()) > 0)
			xivap.uiWindow.addMessage(colRed, "Error de conexion: " + _socket.errorMessage());
		return m;
	}

	string str = _socket.readln();
 
	if(length(str) == 0)
		return m;
	// internal callbacks that dont have to leave the API
	// (authentification, inf request etc)
	do {
//#ifdef FSDAPI_DUMP_COMMUNICATION
		if (xivap.debug.net)
			xivap.addText(colWhite, str, true, true);
//#endif
		if(length(str) == 0)
			str = _socket.readln();

		if(length(str) == 0) {
			str = "invalid";
			continue;
		}

		m.decompose(str);

		switch(m.type) {
			case _FSD_SERVERVERIFY_:
				clientVerify(m);
				str = "";
				break;

			case _FSD_REGINFO_:
				regInfo(m);
				str = "";
				m = FSD::Message();
				break;
		
			case _FSD_INFOREQ_: // INF request packets
				// Client Information
				// TODO: Implementar respuesta a otras peticiones como "CAPS"
				if(m.tokens[0] == _FSD_INFOREQ_INF_) {
					sendInfoReply(m.source);
					str = "";
				} else if(m.tokens[0] == "RN") {
					sendInfoRequestReply(m.source, "RN", _realname);
					str = "";
				} else if(m.tokens[0] == "RV") {
					sendInfoRequestReply(m.source, "RV", _id);
					str = "";
				}
				break;

			case _FSD_KILL_:
				_connected = false;
				_socket.close();
				break;

			case _FSD_PING_:
				sendPong(m);
				str = "";
				break;

			case _FSD_ERROR_:
				_connected = _socket.connected();
				break;

			case _FSD_PLANEINFO_:
				if(length(m.tokens[0]) > 4) {
					// convert MTL string to CSL alias, if it is set
					string ac = copy(m.tokens[0], 0, 4); // aircraft code
					string s = m.tokens[0];
					del(s, 0, 4); // rest without aircraft code

					// look up this MTL code...
					AliasMap::iterator it = _cslAliases.find(pconst(s));
					// and replace it with the CSL alias if found
					if(it != _cslAliases.end())
						m.tokens[0] = ac + string(it->second.c_str());
				}
				break;

			case _FSD_CUSTOMPILOT_: // A�adido para la red de AHS comando "#SB" con par�metros "PI" (recepci�n de plane info) y "FSIP2P" (probablemente recepci�n de plane info exclusiva de FSINN)
				//TODO: Descubrir significado de los tres primeros par�metros (tokens[1]="X", tokens[2]="0" y tokens[3]="0")
				if (m.tokens[0] == _FSD_CUSTOMPILOT_PLANEINFO_) // Comando "PI" (recepci�n de plane info)
				{
					string ac0 = m.tokens[4]; // ICAO de aeronave
					if (ac0[0] == '~') del(ac0,0,1); // Borra el primer car�cter "~" que suele mandar la red (no s� si significar� algo)
					m.tokens[4] = ac0;
					if(length(ac0) > 4) {
						// convert MTL string to CSL alias, if it is set
						string ac = copy(ac0, 0, 4); // aircraft code
						string s = ac0;
						del(s, 0, 4); // rest without aircraft code

						// look up this MTL code...
						AliasMap::iterator it = _cslAliases.find(pconst(s));
						// and replace it with the CSL alias if found
						if(it != _cslAliases.end())
							m.tokens[4] = ac + string(it->second.c_str());
					}
				}
				else if(m.tokens[0] == _FSD_CUSTOMPILOT_REQPLANEINFO_) // recepci�n de petici�n c�digo ICAO propio desde una aeronave conectada a la red de AHS
					{
						sendPlaneInfo(xivap.acType(), m.source); // Env�a c�digo ICAO (MTL) al piloto (cliente) que lo ha solicitado
					}
	
				break;

			default:
				break;
		}
	} while(length(str) == 0);

	return m;
}

FSD::Message FsdAPI::testreceive(string str) // A�adido para comando "TEST"
{
	FSD::Message m;

	if(length(str) == 0)
		return m;
	// internal callbacks that dont have to leave the API
	// (authentification, inf request etc)
	do {
		xivap.addText(colWhite, str, true, true);
		if(length(str) == 0) {
			str = "invalid";
			continue;
		}

		m.decompose(str);

		switch(m.type) {
			case _FSD_SERVERVERIFY_:
				clientVerify(m);
				str = "";
				break;

			case _FSD_REGINFO_:
				regInfo(m);
				str = "";
				m = FSD::Message();
				break;
		
			case _FSD_INFOREQ_: // INF request packets
				// Client Information
				// TODO: Implementar respuesta a otras peticiones como "CAPS"
				if(m.tokens[0] == _FSD_INFOREQ_INF_) {
					sendInfoReply(m.source);
					str = "";
				} else if(m.tokens[0] == "RN") {
					sendInfoRequestReply(m.source, "RN", _realname);
					str = "";
				} else if(m.tokens[0] == "RV") {
					sendInfoRequestReply(m.source, "RV", _id);
					str = "";
				}
				break;

			case _FSD_KILL_:
				_connected = false;
				_socket.close();
				break;

			case _FSD_PING_:
				sendPong(m);
				str = "";
				break;

			case _FSD_ERROR_:
				_connected = _socket.connected();
				break;

			case _FSD_PLANEINFO_:
				if(length(m.tokens[0]) > 4) {
					// convert MTL string to CSL alias, if it is set
					string ac = copy(m.tokens[0], 0, 4); // aircraft code
					string s = m.tokens[0];
					del(s, 0, 4); // rest without aircraft code

					// look up this MTL code...
					AliasMap::iterator it = _cslAliases.find(pconst(s));
					// and replace it with the CSL alias if found
					if(it != _cslAliases.end())
						m.tokens[0] = ac + string(it->second.c_str());
				}
				break;

			case _FSD_CUSTOMPILOT_: // A�adido para la red de AHS comando "#SB" con par�metros "PI" (recepci�n de plane info) y "FSIP2P" (probablemente recepci�n de plane info exclusiva de FSINN)
				//TODO: Descubrir significado de los tres primeros par�metros (tokens[1]="X", tokens[2]="0" y tokens[3]="0")
				if (m.tokens[0] == _FSD_CUSTOMPILOT_PLANEINFO_) // Comando "PI" (recepci�n de plane info)
				{
					string ac0 = m.tokens[4]; // ICAO de aeronave
					if (ac0[0] == '~') del(ac0,0,1); // Borra el primer car�cter "~" que suele mandar la red (no s� si significar� algo)
					m.tokens[4] = ac0;
					if(length(ac0) > 4) {
						// convert MTL string to CSL alias, if it is set
						string ac = copy(ac0, 0, 4); // aircraft code
						string s = ac0;
						del(s, 0, 4); // rest without aircraft code

						// look up this MTL code...
						AliasMap::iterator it = _cslAliases.find(pconst(s));
						// and replace it with the CSL alias if found
						if(it != _cslAliases.end())
							m.tokens[4] = ac + string(it->second.c_str());
					}
				}
				else if(m.tokens[0] == _FSD_CUSTOMPILOT_REQPLANEINFO_) // recepci�n de petici�n c�digo ICAO propio desde una aeronave conectada a la red de AHS
					{
						sendPlaneInfo(xivap.acType(), m.source); // Env�a c�digo ICAO (MTL) al piloto (cliente) que lo ha solicitado
					}
	
				break;

			default:
				break;
		}
	} while(length(str) == 0);

	return m;
}

void FsdAPI::sendInfoRequestReply(string dest, string request, string reply)
{
	FSD::Message m;

	m.type = _FSD_INFOREPLY_;
	m.source = _callsign;
	m.dest = dest;
	m.tokens.push_back(request);
	m.tokens.push_back(reply);
	send(m, false);
}

void FsdAPI::sendPong(const FSD::Message& m)
{
	// source dest time
	// $POEBBR_APP:N1697J:TIME
	FSD::Message reply;

	reply.type = _FSD_PONG_;
	reply.source = _callsign;
	reply.dest = m.source;
	reply.tokens.push_back(m.tokens[0]);

	send(reply);
}

void FsdAPI::regInfo(const FSD::Message& m)
{
       // **************************                                                                           
       // removed on request by IVAO                                                                           
       // **************************

       _verified = true;
       _verificationCallback();
}

bool FsdAPI::send(FSD::Message &msg, bool colon_check)
{
	// don't send shit to a non-verified connection
	if(!_verified && msg.type != _FSD_CLIENTVERIFY_ && msg.type != _FSD_ADDPILOT_ && msg.type != _FSD_ADDATC_)
		return false;

	if(!_connected)
		return false;

	if(!_socket.connected()) {
		_connected = false;
		if(length(_socket.errorMessage()) > 0)
			xivap.uiWindow.addMessage(colRed, "Error de conexion: " + _socket.errorMessage());
		return false;
	}

	string line = msg.compose(colon_check);
	if(length(line) > 0 && length(line) < MAX_FSD_PACKETLEN) {
		_socket.writeln(line);
//#ifdef FSDAPI_DUMP_COMMUNICATION
//		xivap.addText(colLightGray, line);
		if (xivap.debug.net)
			xivap.addText(colLightGray, line, true, true); // Tambi�n a log.txt (��CUIDADO: Se grabar� tambi�n la contrase�a!!)
//#endif
		return true;
	}
	return false;
}

void FsdAPI::clientVerify(const FSD::Message& m)
{
	
       // from server: source dest revision seed
       // !SSERVER:DAT120M:0:1234567890
  
       // **************************                                                                                              
       // removed on request by IVAO                                                                                              
       // ************************** 
       
       _connected = true;
}

void FsdAPI::sendInfoReply(const string& dest)
{
		
	// send INF reply to the sender
	string reply = string(FSD_SOFTWARE_NAME) + " " + SOFTWARE_VERSION 
#ifdef IVAO
		+ " IVAO"
#endif
		+ " (" + xivap.revision() + ") " + PLATFORM 
		+ " - " + _realname + " (" + _id + ") MTL " + _mtl
		+ " - PrvIP " + _socket.ip() + " PubIP "
		+ _mypublicip + " - Srv " + _host;

	if(_usingWX) reply += " - WX on";
	else reply += " - WX off";

	if(xivap.autopilotOn())
		reply += " - AP on: [" + xivap.autopilotState() + "]";
	else
		reply += " - AP off";
	
	reply += " - P2P " + itostring(xivap.p2pmode());

	sendMessage(dest, reply);
}

void FsdAPI::sendMessage(string destination, string message)
{
	FSD::Message m;

	m.type = _FSD_TEXTMESSAGE_;
	m.source = _callsign;
	m.dest = stripcolons(destination);
	m.tokens.push_back(stripcolons(message));
	send(m);
}

void FsdAPI::sendPilotPos(IdentMode ident, int transponder, float lat, float lon, int alt,
						  int speed, float pitch, float bank, float hdg, bool onground, int pressurealt)
{

	if(!_connected)
		return;

	// ident callsign transponder rating latitude longitude truealt speed pitchbankheading
	// @N:N169J:1200:3:43.12345:-78.543:12000:120:3487239347:60
	FSD::Message pos;
	pos.type = _FSD_PILOTPOS_;
	switch(ident) {
		case IdentSby:	pos.source = "S"; break;
		case IdentC:	pos.source = "N"; break;
		case IdentID:	pos.source = "Y"; break;
	}

	pos.dest = _callsign;

	string xpdrstr = itostring(transponder);
	while(length(xpdrstr) < 4) xpdrstr = "0" + xpdrstr;
	while(length(xpdrstr) > 4) del(xpdrstr, 0, 1);
	for(int i = 0; i < 4; ++i)
		if(xpdrstr[i] < '0' || xpdrstr[i] > '7') xpdrstr[i] = '0';
	pos.tokens.push_back(xpdrstr);
	
	_rating = 1; // En la red de AHS no parece haber ratings
	pos.tokens.push_back(itostring(_rating));
	pos.tokens.push_back(ftoa(lat));
	pos.tokens.push_back(ftoa(lon));
	pos.tokens.push_back(itostring(alt));
	pos.tokens.push_back(itostring(speed));

	FSD::FS_PBH pbh;
	pbh.pbh = 0;
	pbh.pitch = static_cast<int>(pitch * PITCH_MULTIPLIER);
	pbh.bank = static_cast<int>(bank * BANK_MULTIPLIER);
	pbh.hdg = static_cast<int>(hdg * HDG_MULTIPLIER);
	if(onground) pbh.onground = 1;

	pos.tokens.push_back(itostring(pbh.pbh));

	int altdiff = pressurealt - alt;
	pos.tokens.push_back(itostring(altdiff));

	send(pos);

	//A�adido para enviar "plane params" como estado de luces y de motores, esperando no saturar demasiado la red, en caso de que se env�e, porque se manda a todos los clientes conectados

//	FSD::Message pparams;
//	pparams.type = _FSD_CUSTOMPILOT_;
//	pparams.source = _callsign;
//	pparams.dest = "*";
//	pparams.tokens.push_back(_FSD_CUSTOMPILOT_PLANEPARAMS_);
//	pparams.tokens.push_back(itostring(xivap.getParams()));

//	send(pparams);

//	xivap.sendPlaneParams();
}

void FsdAPI::decodePBH(const unsigned int pbh, float& pitch, float& bank, float& heading, bool& onground)
{
	FSD::FS_PBH pbhstrct;

	pbhstrct.pbh = pbh;
	pitch = pbhstrct.pitch / PITCH_MULTIPLIER;
	bank = pbhstrct.bank / BANK_MULTIPLIER;
	heading = pbhstrct.hdg / HDG_MULTIPLIER;
	onground = pbhstrct.onground == 1;
}

void FsdAPI::disconnectGhostPilot(string callsign)
{
	
	string packet = FSD_HEADS[_FSD_DELPILOT_] + callsign;
	_socket.writeln(packet);
//	_socket.close();
//	_connected = false;
//	_params.params = 0;
}

void FsdAPI::disconnectPilot()
{
	
	string packet = FSD_HEADS[_FSD_DELPILOT_] + _callsign;
	_socket.writeln(packet);
	_socket.close();
	_connected = false;
// Quitado para que no falle al reconectar
//	_verified = false; 
	_params.params = 0;
}

bool FsdAPI::sendFlightplan(Flightplan& fpl)
{
	if(!_connected) return false;

//TODO: Sacar informaci�n del tipo de motor del avi�n para enviarlo
	char t_aero, n_motores, t_motor, cat_et;
	string icaoPV = fpl.aircrafttype;
	if(length(icaoPV) > 4) {
		icaoPV = copy(icaoPV, 0, 4); //B727aaaxxxxx -> B727
	}
	AircraftDB::Aircraft aeronave = xivap.aircraftDB.get(icaoPV); // Busca los datos de la aeronave del ICAO indicado
	string tipo = aeronave.type; // Tipo de aeronave (formato "L2P")

	if (xivap.debug.multiplayer)
	{
		xivap.addText(colRed, "Se ha encontrado el 'equipo' " + tipo + " para el ICAO " + icaoPV);
	}

	if (length(tipo) == 3)
	{
		t_aero = tipo[0]; // "L"
		n_motores = tipo[1]; // "2"
		t_motor = tipo[2]; // "P"
	}
	else // si no se encuentra el tipo, poner aeronave tipo avi�n con un motor de h�lice simple
	{
		t_aero = 'L';
		n_motores = '1';
		t_motor = 'P';
	}
	switch (t_motor) { // FIXME: Especulaci�n sobre la correspondencia de primer par�metro del "aircraft" del PV del FSInn con el tipo de motor de la aeronave (podr�a estar equivocado)
		case 'P':
			t_motor = 'T';
			break;
		case 'J':
			t_motor = 'L';
			break;
		case 'H':
			t_motor = 'H';
			break;
		case 'T':
			t_motor = 'B';
			break;
		default:
			t_motor = 'T';
			break;
	}
	if (t_aero == 'H') t_motor = 'H'; // Asegura que los helic�pteros se env�an como "H"

//	cat_et = aeronave.category; // Categor�a de estela turbulenta ("L", "M", "H", "V" o "X", sin definir)
	if (length(fpl.wtc) == 1) cat_et = fpl.wtc[0]; // Categor�a de estela turbulenta ("L", "M", "H", "V" o "X", sin definir)
	else cat_et = 'X';

	char t_equipo = 'G';

	// compose flightplan packet
	FSD::Message m;
	m.type = _FSD_FLIGHTPLAN_;
	m.source = _callsign;
	m.dest = _FSD_SERVERDEST_;
	m.tokens.push_back(fpl.flightrules);
//	m.tokens.push_back(fpl.aircraft());
	string ac_PV = string(t_motor) + '/' + icaoPV + '/' + string(t_equipo);
	m.tokens.push_back(ac_PV); // Tipo de aeronave al estilo FSInn
//	m.tokens.push_back(fpl.speedtype + fpl.cruisespeed); // El AhsRadar no reconoce el tipo de velocidad, s�lo el n�mero
	m.tokens.push_back(fpl.cruisespeed);
	m.tokens.push_back(fpl.departure);
	m.tokens.push_back(fpl.deptimeest);
	m.tokens.push_back(fpl.deptimeact);
	if (fpl.alttype == "VFR") m.tokens.push_back(fpl.alttype); // Si el tipo de altitud es "VFR", no enviar el dato num�rico de altitud
	else m.tokens.push_back(fpl.alttype + fpl.cruisealt); // Si es "A" o "N", enviarlo junto con el dato num�rico de altitud
	m.tokens.push_back(fpl.destination);
	m.tokens.push_back(fpl.hoursenroute);
	m.tokens.push_back(fpl.minenroute);
	m.tokens.push_back(fpl.hoursfuel);
	m.tokens.push_back(fpl.minfuel);
	m.tokens.push_back(fpl.alternate);
	m.tokens.push_back(fpl.remarks);
	m.tokens.push_back(fpl.route);
	m.tokens.push_back(fpl.typeofflight);
	m.tokens.push_back(fpl.pob);
	m.tokens.push_back(fpl.alternate2);

	//xivap.addText(colWhite, "flightplan string: " + m.compose());

	// ...and send it
	return send(m);
}

Flightplan FsdAPI::getFlightplan(const FSD::Message& m)
{
	Flightplan result;

	result.cruisespeed = m.tokens[0];

	if(result.cruisespeed[0] < '0' || result.cruisespeed[0] > '9') {
		result.speedtype = result.cruisespeed[0];
		del(result.cruisespeed, 0, 1);
	}

	result.departure = m.tokens[1];
	result.deptimeest = m.tokens[2];
	result.deptimeact = m.tokens[3];
	result.cruisealt = m.tokens[4];
	result.destination = m.tokens[5];
	result.hoursenroute = m.tokens[6];
	result.minenroute = m.tokens[7];
	result.alternate = m.tokens[8];
	result.remarks = m.tokens[9];
	result.route = m.tokens[10];

	result.normalize();

	return result;
}

string FsdAPI::getMETAR(string estacion)
{
	string rMETAR = "ERROR";
	sendWxRequest(FSD::WX_METAR, estacion);
	FSD::Message m;
	m = receive();
	float temporiz = XPLMGetElapsedTime();
	float temporiz2 = XPLMGetElapsedTime();
	
	while (!(m.type == _FSD_WEADATA_RC_AHS_ && m.tokens[0] == _FSD_WEADATA_METAR_AHS_) && !(m.type == _FSD_ERROR_ && m.tokens[0] == "009") && m.source != callsign() && temporiz < temporiz2 + 2) // Espera a que haya mensaje de METAR o error hasta dos segundos (para no paralizar demasiado) FIXME: �Se podr�a hacer de otra forma?
	{ 
		temporiz = XPLMGetElapsedTime(); 
		m = receive();
	}

//FIXME:DEBUG
	if (xivap.debug.weather > 0)
		xivap.addText(colRed, "Recuperando METAR de " + estacion, true, true);

	if (m.tokens[0] == _FSD_WEADATA_METAR_AHS_) rMETAR = m.tokens[1]; // si se recibe METAR, lo copia para devolverlo
	return rMETAR;
}

	void FsdAPI::sendWxRequest(FSD::WeatherType what, string station)
{
	station = trim(strupcase(station));
	if(length(station) <= 2) return;
	if(length(station) > 4) return;

	FSD::Message m;
	// Compatibilizado con AHS
//	m.type = _FSD_WEADATA_;
	m.type = _FSD_WEADATA_RQ_AHS_;
	m.source = _callsign;
	m.dest = _FSD_SERVERDEST_;
//	m.tokens.push_back(itostring(what));
	m.tokens.push_back(_FSD_WEADATA_METAR_AHS_);
	m.tokens.push_back(station);
	send(m);
}

void FsdAPI::sendInfoRequest(string dest, string request)
{
	dest = trim(dest);
	if(length(dest) < 3) return;
	request = trim(request);
	if(length(request) < 1) return;

	FSD::Message m;
	m.type = _FSD_INFOREQ_;
	m.source = _callsign;
	m.dest = dest;
	m.tokens.push_back(request);
	send(m, false);
}

bool FsdAPI::setParams(FSD::PlaneParams p, string dest)
{
	if(!(_verified && _connected))
		return false;				// don't send the info yet

	if(p.params == _params.params)
		return false;				// params did not change

//#ifdef PARAMS_DEBUG
	//FIXME: DEBUG
	if (xivap.debug.params)
	{
		string debug = "ENVIANDO PLANE PARAMS: Gear:" + itostring(_params.gear)
			+ " Bcn:" + itostring(p.beaconLight)
			+ " Lnd:" + itostring(p.landLight)
			+ " Nav:" + itostring(p.navLight)
			+ " Strb:" + itostring(p.strobeLight)
			+ " Txi:" + itostring(p.taxiLight)
			+ " ThRev:" + itostring(p.thrustReversers)
			+ " E1:" + itostring(p.engine1Running)
			+ " E2:" + itostring(p.engine2Running)
			+ " E3:" + itostring(p.engine3Running)
			+ " E4:" + itostring(p.engine4Running)
			+ " Flps:" + itostring(p.flapsRatio)
			+ " SpdBrk:" + itostring(p.speedbrakeRatio)
			+ " Thrtle:" + itostring(p.thrustRatio);
		xivap.addText(colGray, debug, true, true);
	}
//#endif
// Quitado para compatibilidad con red AHS
//	FSD::Message m;
//	m.type = _FSD_PLANEPARAMS_;
//	m.source = _callsign;
//	m.dest = _FSD_SERVERDEST_;

//	m.tokens.push_back(itostring(p.params));

//A�adido para enviar "plane params" como estado de luces y de motores, esperando no saturar demasiado la red, en caso de que se env�e, porque se manda a todos los clientes conectados

	FSD::Message pparams;
	pparams.type = _FSD_CUSTOMPILOT_;
	pparams.source = _callsign;
//	pparams.dest = "*";
	pparams.dest = dest;
	pparams.tokens.push_back(_FSD_CUSTOMPILOT_PLANEPARAMS_);
//	pparams.tokens.push_back(itostring(xivap.getParams()));
	pparams.tokens.push_back(itostring(p.params));

	if(send(pparams)) {
		_params.params = p.params;
		return true;
	}
	return false;
}

void FsdAPI::subscribeWeather()
{
	if(!_connected || !_verified) {
		_sendSubscribeWX = true;
		return;
	}

//	FSD::Message m;
//	m.type = _FSD_WEAREG_;
//	m.source = _callsign;
//	m.dest = _FSD_SERVERDEST_;
//	m.tokens.push_back("1");
//	if(send(m)) {
		_sendSubscribeWX = false;
		_usingWX = true;
//	}
	// A�adido para hacer petici�n de METARs de ADs del FP por adelantado, para meterlos en la dB de meteorolog�a con sus METARs
	if (xivap.fpl.departure != "") sendWxRequest(FSD::WX_METAR, xivap.fpl.departure);
	if (xivap.fpl.destination != "") sendWxRequest(FSD::WX_METAR, xivap.fpl.destination);
	if (xivap.fpl.alternate != "") sendWxRequest(FSD::WX_METAR, xivap.fpl.alternate);
	if (xivap.fpl.alternate2 != "") sendWxRequest(FSD::WX_METAR, xivap.fpl.alternate2);

}

void FsdAPI::unsubscribeWeather()
{
	_sendSubscribeWX = false;
	_usingWX = false;
//	FSD::Message m;
//	m.type = _FSD_WEAREG_;
//	m.source = _callsign;
//	m.dest = _FSD_SERVERDEST_;
//	m.tokens.push_back("0");
//	send(m);
}

void FsdAPI::sendVoice(bool status)
{
	if(!_connected || !_verified) {
		_sendVoice = true;
		_usingVoice = status;
		return;
	}
// Quitado por no ser compatible con red AHS
//	FSD::Message m;
//	m.type = _FSD_NOVOICE_;
//	m.source = _callsign;
//	m.dest = _FSD_SERVERDEST_;
//	m.tokens.push_back(_callsign);
//	if(status) m.tokens.push_back("1");
//	else m.tokens.push_back("0");
//	if(send(m))
		_sendVoice = false;
}

void FsdAPI::_verificationCallback()
{
	if(_sendSubscribeWX) subscribeWeather();
//	if(_sendPlaneInfo) sendPlaneInfo(_mtl);
	if(_sendPlaneInfo) sendPlaneInfo(_mtl,"dummy");
	if(_sendVoice) sendVoice(_usingVoice);
}

void FsdAPI::sendPlaneInfo(string mtl, string dcallsign)
{	
	if(!_connected || !_verified) {
		_sendPlaneInfo = true;
		_mtl = mtl;
		return;
	}
	_sendPlaneInfo = false;
	_mtl = mtl;
	// look up the CSL alias table: if the _mtl string is in there,
	// send the corresponding alias
	// alias table contains MTL -> CSL mapping (file is the other way around)
	if(length(_mtl) > 4) {
		string ac = copy(_mtl, 0, 4);
		string s = _mtl;
		del(s, 0, 4);
		AliasMap::iterator it = _cslAliases.begin();
		bool found = false;
		while(it != _cslAliases.end() && !found) {
			if(it->second.c_str() == s) {
				found = true;
				_mtl = ac + string(it->first.c_str());
			}
			++it;
		}
	}

	// don't send 5 letter CSL livery codes. If the livery code exceeds
	// 3 characters, remove it
//	if(length(_mtl) > 10) {
//		_mtl = copy(mtl, 0, 10); //B727aaaxxxxx -> B727aaaxxx
	if(length(_mtl) > 4) {
		_mtl = copy(_mtl, 0, 4); //B727aaaxxxxx -> B727
	}

// No soportado por la red de AHS
//	FSD::Message m;
//	m.type = _FSD_PLANEINFO_;
//	m.source = _callsign;
//	m.dest = _FSD_SERVERDEST_;
//	m.tokens.push_back(_mtl);
//	send(m);

//TODO: Sacar informaci�n del tipo de motor del avi�n para enviarlo
	char t_aero, n_motores, t_motor, cat_et;

	if(length(mtl) > 4) {
		mtl = copy(mtl, 0, 4); //B727aaaxxxxx -> B727
	}
	AircraftDB::Aircraft aeronave = xivap.aircraftDB.get(mtl); // Busca los datos de la aeronave del ICAO indicado
	string tipo = aeronave.type; // Tipo de aeronave (formato "L2P")
	if (length(tipo) == 3)
	{
		t_aero = tipo[0]; // "L"
		n_motores = tipo[1]; // "2"
		t_motor = tipo[2]; // "P"
	}
	else // si no se encuentra el tipo, poner aeronave tipo avi�n con un motor de h�lice simple
	{
		t_aero = 'L';
		n_motores = '1';
		t_motor = 'P';
	}
	switch (t_motor) {
		case 'P':
			t_motor = '0';
			break;
		case 'J':
			t_motor = '1';
			break;
		case 'H':
			t_motor = '3';
			break;
		case 'T':
			t_motor = '5';
			break;
		default:
			t_motor = '0';
			break;
	}
	if (t_aero == 'H')
	{
		t_motor = '3'; // Asegura que los helic�pteros se mandan como tipo "3"
		cat_et = 'V';
	}
	else cat_et = aeronave.category; // Categor�a de estela turbulenta ("L", "M", "H", "V" o "X", sin definir)


// Env�o de plane info (MTL-CSL) para la red AHS
	FSD::Message m;
	m.type = _FSD_CUSTOMPILOT_; // Comando de env�o-recepci�n piloto a piloto
	m.source = _callsign;
	m.dest = dcallsign; // Se env�a la informaci�n dirigida hacia el piloto (cliente) que la ha solicitado
	m.tokens.push_back(_FSD_CUSTOMPILOT_PLANEINFO_); // Comando plane info ("PI")
//	m.tokens.push_back("X"); // Par�metro que al parecer se manda siempre (podr�a ser categor�a de estela turbulenta "L", "M" o "H", siendo la "X" sin definir)
	m.tokens.push_back(cat_et); // Manda la categor�a de estela turbulenta -> ��� PROBAR !!!
	m.tokens.push_back("0"); // Par�metro que al parecer se manda siempre
//	m.tokens.push_back("0"); // Par�metro que creo que est� entre 0 y 5 (Tipo de motor: 0 =  Piston (P); 1 = Jet (J); 2 = None; 3 = Helo-turbine (H); 4 = Rocket (no soportado); 5 = Turboprop (T))
	m.tokens.push_back(t_motor); // Par�metro que creo que est� entre 0 y 5 (Tipo de motor: 0 =  Piston (P); 1 = Jet (J); 2 = None; 3 = Helo-turbine (H); 4 = Rocket (no soportado); 5 = Turboprop (T))
	m.tokens.push_back("~"+_mtl);  // "~" (parece que se env�a siempre) + ICAO de la aeronave
	send(m);


	// FIXME: DEBUG
	if (xivap.debug.multiplayer)
	{
		string mtldebug = "ENVIANDO PLANE INFO: " + _mtl;
//		xivap.addText(colGray, _mtl, false, true);
//		xivap.addText(colGray, m.compose(), false, true);
		xivap.addText(colGray, _mtl, true, true);
		xivap.addText(colGray, m.compose(), true, true);
	}
}

void FsdAPI::sendPlaneInfoRequest(const string& callsign)
{
	FSD::Message m;
//	m.type = _FSD_REQPLANEINFO_;
	m.type = _FSD_CUSTOMPILOT_; // Incorporado comando de la red AHS para pedir informaci�n ("#SB:<callsign_src>:<callsign_dst>:PIR")
	m.source = _callsign;
	m.dest = callsign;
	m.tokens.push_back(_FSD_CUSTOMPILOT_REQPLANEINFO_); // Comando "PIR"
	send(m);
}

void FsdAPI::sendPlaneParamsRequest(const string& callsign)
{
	FSD::Message m;
	m.type = _FSD_REQPLANEPARAMS_;
	m.source = _callsign;
	m.dest = callsign;
	send(m);
}

void FsdAPI::sendKill(string callsign, string reason)
{
	reason = "Killed by " + _callsign + ": " + reason;

	FSD::Message m;
	m.type = _FSD_KILL_;
	m.source = _callsign;
	m.dest = callsign;
	m.tokens.push_back(reason);
	send(m);
}
