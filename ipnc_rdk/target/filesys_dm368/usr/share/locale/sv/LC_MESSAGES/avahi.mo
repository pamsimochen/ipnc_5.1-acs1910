��    �      ,  �   <      �
  �  �
  h   �  �     i  �    ]  �   }          &     9  !   G     i     �     �      �     �     �  	   	  '     '   ;  4   c  *   �  .   �  
   �     �               1     C     `     x     �     �     �     �     �     �          !     7     L     e     x     �     �     �     �     �          &  %   F  &   l  #   �  #   �  #   �  !   �  (   !  <   J  %   �     �      �     �  #        /     O  #   g  %   �  ?   �     �  %        +     ;     K     ]     u     �     �     �     �     �     �     �             4   *     _     q     �     �     �     �     �     �                     5     F  '   K     s  &   �  	   �     �     �     �     �     �     �  "        6     C  "   L  4   o     �     �     �     �     �     �               $  
   <  &   G  '   n  ,   �     �     �     �      �  C    �  ]   r   5#    �#  u  �$  :  ,&  �   g(     )     )     /)  %   >)     d)     )     �)      �)     �)     �)     *  .   *  .   F*  @   u*  0   �*  5   �*  
   +  
   (+     3+     D+     U+     f+     +     �+     �+     �+     �+     �+     �+     �+     ,     ,     1,  "   B,     e,  	   },      �,     �,     �,     �,  (   �,  )   #-  5   M-  .   �-  0   �-  1   �-  ,   .  /   B.  )   r.  9   �.  K   �.  /   "/  )   R/  *   |/  0   �/  6   �/  '   0      70  0   X0  3   �0  O   �0     1     !1     @1     M1     ^1     p1     �1     �1     �1     �1     �1     �1     �1     �1     2     !2  9   <2     v2     �2     �2     �2     �2     �2     �2     �2     3     13     93     M3     ]3  '   b3     �3  0   �3     �3     �3     �3     4     4     4  !   04  !   R4     t4     �4  *   �4  >   �4     �4     5     5     05     E5     X5     k5     o5     �5  
   �5  ,   �5  -   �5  2   6     76     R6  !   d6  &   �6        A   <       s               N       h   r       E   H   )   ^       ]   "      z   $   L   5   t           J      }   \   *   9       k   %               W      o   K   ~   v          7         2   @   b   '   �   (       B   w   e   p   :      .   x                     c   Q          F      j   #   n                       >   d   D   {       R           l          |   	      g                             O   !   3      a   1   f   U      �   y   6      Y   [      S       ,   i   
   ?      m       Z          C      &       /   =      �   ;   _   G   P   8                   +   X       4   u   `      0   -       q   M   T               V       I        -h --help            Show this help
    -V --version         Show version
    -D --browse-domains  Browse for browsing domains instead of services
    -a --all             Show all services, regardless of the type
    -d --domain=DOMAIN   The domain to browse in
    -v --verbose         Enable verbose mode
    -t --terminate       Terminate after dumping a more or less complete list
    -c --cache           Terminate after dumping all entries from the cache
    -l --ignore-local    Ignore local services
    -r --resolve         Resolve services found
    -f --no-fail         Don't fail if the daemon is not available
    -p --parsable        Output in parsable format
     -k --no-db-lookup    Don't lookup service types
    -b --dump-db         Dump service type database
 %s [options]

    -h --help            Show this help
    -s --ssh             Browse SSH servers
    -v --vnc             Browse VNC servers
    -S --shell           Browse both SSH and VNC
    -d --domain=DOMAIN   The domain to browse in
 %s [options] %s <host name ...>
%s [options] %s <address ... >

    -h --help            Show this help
    -V --version         Show version
    -n --name            Resolve host name
    -a --address         Resolve address
    -v --verbose         Enable verbose mode
    -6                   Lookup IPv6 address
    -4                   Lookup IPv4 address
 %s [options] %s <name> <type> <port> [<txt ...>]
%s [options] %s <host-name> <address>

    -h --help            Show this help
    -V --version         Show version
    -s --service         Publish service
    -a --address         Publish address
    -v --verbose         Enable verbose mode
    -d --domain=DOMAIN   Domain to publish service in
    -H --host=DOMAIN     Host where service resides
       --subtype=SUBTYPE An additional subtype to register this service with
    -f --no-fail         Don't fail if the daemon is not available
 %s [options] <new host name>

    -h --help            Show this help
    -V --version         Show version
    -v --verbose         Enable verbose mode
 : All for now
 : Cache exhausted
 Access denied An unexpected D-Bus error occured Avahi SSH Server Browser Avahi VNC Server Browser Avahi client failure: %s Avahi domain browser failure: %s Avahi resolver failure: %s Bad number of arguments
 Bad state Browse for Zeroconf-enabled SSH Servers Browse for Zeroconf-enabled VNC Servers Browsing for service type %s in domain %s failed: %s Browsing for services in domain <b>%s</b>: Browsing for services on <b>local network</b>: Canceled.
 Change domain Choose SSH server Choose Shell Server Choose VNC server Client failure, exiting: %s
 Connecting to '%s' ...
 DNS failure: FORMERR DNS failure: NOTAUTH DNS failure: NOTIMP DNS failure: NOTZONE DNS failure: NXDOMAIN DNS failure: NXRRSET DNS failure: REFUSED DNS failure: SERVFAIL DNS failure: YXDOMAIN DNS failure: YXRRSET Daemon connection failed Daemon not running Desktop Disconnected, reconnecting ...
 E Ifce Prot %-*s %-20s Domain
 E Ifce Prot Domain
 Established under name '%s'
 Failed to add address: %s
 Failed to add service: %s
 Failed to add subtype '%s': %s
 Failed to connect to Avahi server: %s Failed to create address resolver: %s
 Failed to create browser for %s: %s Failed to create client object: %s
 Failed to create domain browser: %s Failed to create entry group: %s
 Failed to create host name resolver: %s
 Failed to create resolver for %s of type %s in domain %s: %s Failed to create simple poll object.
 Failed to parse address '%s'
 Failed to parse port number: %s
 Failed to query host name: %s
 Failed to query version string: %s
 Failed to read Avahi domain: %s Failed to register: %s
 Failed to resolve address '%s': %s
 Failed to resolve host name '%s': %s
 Failed to resolve service '%s' of type '%s' in domain '%s': %s
 Host name conflict
 Host name successfully changed to %s
 Initializing... Invalid DNS TTL Invalid DNS class Invalid DNS return code Invalid DNS type Invalid Error Code Invalid RDATA Invalid address Invalid argument Invalid configuration Invalid domain name Invalid flags Invalid host name Invalid interface index Invalid number of arguments, expecting exactly one.
 Invalid operation Invalid packet Invalid port number Invalid protocol specification Invalid record Invalid record key Invalid service name Invalid service subtype Invalid service type Is empty Local name collision Memory exhausted Name Name collision, picking new name '%s'.
 No command specified.
 No suitable network protocol available Not found Not permitted Not supported OK OS Error Operation failed Resource record key is pattern Server version: %s; Host name: %s
 Service Name Terminal The object passed in was not valid The requested operation is invalid because redundant Timeout reached Too few arguments
 Too many arguments
 Too many clients Too many entries Too many objects Type Version mismatch Waiting for daemon ...
 _Domain... avahi_domain_browser_new() failed: %s
 avahi_service_browser_new() failed: %s
 avahi_service_type_browser_new() failed: %s
 execlp() failed: %s
 n/a service_browser failed: %s
 service_type_browser failed: %s
 Project-Id-Version: avahi
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2009-04-14 03:30+0200
PO-Revision-Date: 2009-02-11 12:39+0100
Last-Translator: Daniel Nylander <po@danielnylander.se>
Language-Team: Swedish <tp-sv@listor.tp-sv.se>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
     -h --help            Visa denna hjälp
    -V --version         Visa version
    -D --browse-domains  Bläddra efter bläddringsdomäner istället för tjänster
    -a --all             Visa alla tjänster, oavsett typen
    -d --domain=DOMÄN    Domänen att bläddra i
    -v --verbose         Aktivera informativt läge
    -t --terminate       Avsluta efter dumpning av en mer eller mindre komplett lista
    -c --cache           Avsluta efter dumpning av alla poster från cachen
    -l --ignore-local    Ignorera lokala tjänster
    -r --resolve         Slå upp tjänster som hittats
    -f --no-fail         Misslycka inte om demonen inte är tillgänglig
    -p --parsable        Skriv ut i tolkningsbart format
     -k --no-db-lookup    Slå inte upp tjänstetyper
    -b --dump-db         Dumpa databasen över tjänstetyper
 %s [flaggor]

    -h --help            Visa denna hjälp
    -s --ssh             Bläddra bland SSH-servrar
    -v --vnc             Bläddra bland VNC-servrar
    -S --shell           Bläddra bland både SSH och VNC
    -d --domain=DOMÄN    Domänen att bläddra i
 %s [flaggor] %s <värdnamn ...>
%s [flaggor] %s <adress ... >

    -h --help            Visa denna hjälp
    -V --version         Visa version
    -n --name            Slå upp värdnamn
    -a --address         Slå upp adress
    -v --verbose         Aktivera informativt läge
    -6                   Slå upp IPv6-adress
    -4                   Slå upp IPv4-adress
 %s [flaggor] %s <namn> <typ> <port> [<txt ...>]
%s [flaggor] %s <värdnamn> <adress>

    -h --help            Visa denna hjälp
    -V --version         Visa version
    -s --service         Publicera tjänst
    -a --address         Publicera adress
    -v --verbose         Aktivera informativt läge
    -d --domain=DOMÄN    Domän att publicera tjänst i
    -H --host=DOMÄN      Värd där tjänsten finns
       --subtype=UNDERTYP En ytterligare undertyp att registrera denna tjänst med
    -f --no-fail         Misslycka inte om demonen inte är tillgänglig
 %s [flaggor] <nytt värdnamn>

    -h --help            Visa denna hjälp
    -V --version         Visa version
    -v --verbose         Aktivera informativt läge
 : Alla just nu
 : Cachen är full
 Åtkomst nekad Ett oväntat D-Bus-fel har inträffat Avahi SSH-serverbläddrare Avahi VNC-serverbläddrare Fel i Avahi-klient: %s Fel i Avahi-domänbläddrare: %s Fel i Avahi-uppslag: %s Dåligt antal argument
 Felaktigt tillstånd Bläddra efter Zeroconf-aktiverade SSH-servrar Bläddra efter Zeroconf-aktiverade VNC-servrar Bläddring efter tjänstetypen %s i domänen %s misslyckades: %s Bläddring efter tjänster i domänen <b>%s</b>: Bläddrar efter tjänster på <b>lokalt nätverk</b>: Avbruten.
 Byt domän Välj SSH-server Välj skalserver Välj VNC-server Klientfel, avslutar: %s
 Ansluter till "%s"...
 DNS-fel: FORMERR DNS-fel: NOTAUTH DNS-fel: NOTIMP DNS-fel: NOTZONE DNS-fel: NXDOMAIN DNS-fel: NXRRSET DNS-fel: REFUSED DNS-fel: SERVFAIL DNS-fel: YXDOMAIN DNS-fel: YXRRSET Anslutning till demon misslyckades Demonen är inte igång Skrivbord Frånkopplad, återansluter ...
 H Grän Prot %-*s %-20s Domän
 H Grän Prot Domän
 Etablerad under namnet "%s"
 Misslyckades att lägga till adress: %s
 Misslyckades att lägga till tjänst: %s
 Misslyckades med att lägga till undertypen "%s": %s
 Misslyckades att ansluta till Avahi-server: %s Misslyckades med att skapa adressuppslagare: %s
 Misslyckades med att skapa bläddrare för %s: %s Misslyckades med att skapa klientobjekt: %s
 Misslyckades med att skapa domänbläddrare: %s Misslyckades med att skapa postgrupp: %s
 Misslyckades med att skapa uppslagare för värdnamn: %s
 Misslyckades med att skapa uppslagare för %s av typen %s i domänen %s: %s Misslyckades med att skapa enkelt poll-objekt.
 Misslyckades med att tolka adressen "%s"
 Misslyckades med att tolka portnummer: %s
 Misslyckades med att fråga efter värdnamn: %s
 Misslyckades med att fråga efter versionssträng: %s
 Misslyckades att läsa Avahi-domän: %s Misslyckades att registrera: %s
 Misslyckades med att slå upp adressen "%s": %s
 Misslyckades med att slå upp värdnamnet "%s": %s
 Misslyckades med att slå upp tjänsten "%s" av typen "%s" i domänen "%s": %s
 Värdnamnskonflikt
 Värdnamnet ändrades till %s
 Initierar... Ogiltigt DNS TTL Ogiltig DNS-klass Ogiltig DNS-svarskod Ogiltig DNS-typ Ogiltig felkod Ogiltig RDATA Ogiltig adress Ogiltigt argument Ogiltig konfiguration Ogiltigt domännamn Ogiltiga flaggor Ogiltigt värdnamn Ogiltigt gränssnittsindex Ogiltigt antal argument, exakt ett argument förväntas.
 Ogiltig åtgärd Ogiltigt paket Ogiltigt portnummer Ogiltig protokollspecifikation Ogiltig post Ogiltig postnyckel Ogiltigt tjänstenamn Ogiltig undertyp för tjänst Ogiltig tjänstetyp Är tom Lokal namnkollision Minnet är slut Namn Namnkollision, väljer nytt namn "%s".
 Inget kommando specificerat.
 Inget lämpligt nätverksprotokoll tillgängligt Hittades inte Inte tillåten Stöds inte OK Operativsystemsfel Åtgärden misslyckades Resursens postnyckel är mönster Serverversion: %s; Värdnamn: %s
 Tjänstenamn Terminal Objektet som skickades in var inte giltigt Den begärda åtgärden är ogiltig därför den är redundant Tidsgräns nåddes För få argument
 För många argument
 För många klienter För många poster För många objekt Typ Versionen stämmer inte Väntar på demon ...
 _Domän... avahi_domain_browser_new() misslyckades: %s
 avahi_service_browser_new() misslyckades: %s
 avahi_service_type_browser_new() misslyckades: %s
 execlp() misslyckades: %s
 Inte tillgänglig service_browser misslyckades: %s
 service_type_browser misslyckades: %s
 