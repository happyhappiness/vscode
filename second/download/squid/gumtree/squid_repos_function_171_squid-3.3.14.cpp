static void
DisplayUsage()
{
    DisplayVersion();
    local_printfx("\n");
    local_printfx("Usage: %s\n", edui_conf.program);
    local_printfx("		-H <host> -p <port> [-Z] [-P] [-v 3] -b <basedn> -s <scope>\n");
    local_printfx("		-D <binddn> -W <bindpass> -F <search-filter> [-G] \n\n");
    local_printfx("	-d	    : Debug Mode.\n");
    local_printfx("	-4	    : Force Addresses to be in IPv4 (127.0.0.1 format).\n");
    local_printfx("	-6	    : Force Addresses to be in IPv6 (::1 format).\n");
    local_printfx("	-H <host>   : Specify hostname/ip of server.\n");
    local_printfx("	-p <port>   : Specify port number. (Range 1-65535)\n");
    local_printfx("	-Z	    : Enable TLS security.\n");
    local_printfx("	-P	    : Use persistent connections.\n");
    local_printfx("	-t <sec>    : Timeout factor for persistent connections.  (Default is 60 sec, set to 0 for never timeout)\n");
    local_printfx("	-v <1,2,3>  : Set LDAP version to 1, 2, or 3.\n");
    local_printfx("	-b <base>   : Specify Base DN. (ie. \"o=ORG\")\n");
    local_printfx("	-s <scope>  : Specify LDAP Search Scope (base, one, sub; defaults to 'one').\n");
    local_printfx("	-D <dn>     : Specify Binding DN. (ie. cn=squid,o=ORG)\n");
    local_printfx("	-W <pass>   : Specify Binding password.\n");
    local_printfx("	-u <attrib> : Set userid attribute (Defaults to \"cn\").\n");
    local_printfx("	-F <filter> : Specify LDAP search filter. (ie. \"(objectClass=User)\")\n");
    local_printfx("	-G 	    : Specify if LDAP search group is required. (ie. \"groupMembership=\")\n");
    local_printfx("	-V	    : Display version & exit.\n");
    local_printfx("	-h	    : This screen & exit.\n");
    local_printfx("\n");
}