int
main(int argc, char **argv)
{
    char buf[1024];
    char *user, *passwd;
    char *ldapServer = NULL;
    LDAP *ld = NULL;
    int tryagain;
    int port = LDAP_PORT;

    setbuf(stdout, NULL);

    while (argc > 1 && argv[1][0] == '-') {
        const char *value = "";
        char option = argv[1][1];
        switch (option) {
        case 'P':
        case 'R':
        case 'z':
        case 'Z':
        case 'd':
        case 'O':
            break;
        default:
            if (strlen(argv[1]) > 2) {
                value = argv[1] + 2;
            } else if (argc > 2) {
                value = argv[2];
                ++argv;
                --argc;
            } else
                value = "";
            break;
        }
        ++argv;
        --argc;
        switch (option) {
        case 'H':
#if !HAS_URI_SUPPORT
            fprintf(stderr, "ERROR: Your LDAP library does not have URI support\n");
            exit(1);
#endif
            /* Fall thru to -h */
        case 'h':
            if (ldapServer) {
                int len = strlen(ldapServer) + 1 + strlen(value) + 1;
                char *newhost = static_cast<char*>(malloc(len));
                snprintf(newhost, len, "%s %s", ldapServer, value);
                free(ldapServer);
                ldapServer = newhost;
            } else {
                ldapServer = xstrdup(value);
            }
            break;
        case 'b':
            basedn = value;
            break;
        case 'f':
            searchfilter = value;
            break;
        case 'u':
            userattr = value;
            break;
        case 'U':
            passwdattr = value;
            break;
        case 's':
            if (strcmp(value, "base") == 0)
                searchscope = LDAP_SCOPE_BASE;
            else if (strcmp(value, "one") == 0)
                searchscope = LDAP_SCOPE_ONELEVEL;
            else if (strcmp(value, "sub") == 0)
                searchscope = LDAP_SCOPE_SUBTREE;
            else {
                fprintf(stderr, PROGRAM_NAME ": ERROR: Unknown search scope '%s'\n", value);
                exit(1);
            }
            break;
        case 'E':
#if defined(NETSCAPE_SSL)
            sslpath = value;
            if (port == LDAP_PORT)
                port = LDAPS_PORT;
#else
            fprintf(stderr, PROGRAM_NAME " ERROR: -E unsupported with this LDAP library\n");
            exit(1);
#endif
            break;
        case 'c':
            connect_timeout = atoi(value);
            break;
        case 't':
            timelimit = atoi(value);
            break;
        case 'a':
            if (strcmp(value, "never") == 0)
                aliasderef = LDAP_DEREF_NEVER;
            else if (strcmp(value, "always") == 0)
                aliasderef = LDAP_DEREF_ALWAYS;
            else if (strcmp(value, "search") == 0)
                aliasderef = LDAP_DEREF_SEARCHING;
            else if (strcmp(value, "find") == 0)
                aliasderef = LDAP_DEREF_FINDING;
            else {
                fprintf(stderr, PROGRAM_NAME ": ERROR: Unknown alias dereference method '%s'\n", value);
                exit(1);
            }
            break;
        case 'D':
            binddn = value;
            break;
        case 'w':
            bindpasswd = value;
            break;
        case 'W':
            readSecret(value);
            break;
        case 'P':
            persistent = !persistent;
            break;
        case 'O':
            bind_once = !bind_once;
            break;
        case 'p':
            port = atoi(value);
            break;
        case 'R':
            noreferrals = !noreferrals;
            break;
#ifdef LDAP_VERSION3
        case 'v':
            switch (atoi(value)) {
            case 2:
                version = LDAP_VERSION2;
                break;
            case 3:
                version = LDAP_VERSION3;
                break;
            default:
                fprintf(stderr, "Protocol version should be 2 or 3\n");
                exit(1);
            }
            break;
        case 'Z':
            if (version == LDAP_VERSION2) {
                fprintf(stderr, "TLS (-Z) is incompatible with version %d\n",
                        version);
                exit(1);
            }
            version = LDAP_VERSION3;
            use_tls = 1;
            break;
#endif
        case 'd':
            debug_enabled = 1;
            break;
        default:
            fprintf(stderr, PROGRAM_NAME ": ERROR: Unknown command line option '%c'\n", option);
            exit(1);
        }
    }

    while (argc > 1) {
        char *value = argv[1];
        if (ldapServer) {
            int len = strlen(ldapServer) + 1 + strlen(value) + 1;
            char *newhost = static_cast<char*>(malloc(len));
            snprintf(newhost, len, "%s %s", ldapServer, value);
            free(ldapServer);
            ldapServer = newhost;
        } else {
            ldapServer = xstrdup(value);
        }
        --argc;
        ++argv;
    }
    if (!ldapServer)
        ldapServer = xstrdup("localhost");

    if (!basedn) {
        fprintf(stderr, "Usage: " PROGRAM_NAME " -b basedn [options] [ldap_server_name[:port]]...\n\n");
        fprintf(stderr, "\t-b basedn (REQUIRED)\tbase dn under which to search\n");
        fprintf(stderr, "\t-f filter\t\tsearch filter to locate user DN\n");
        fprintf(stderr, "\t-u userattr\t\tusername DN attribute\n");
        fprintf(stderr, "\t-s base|one|sub\t\tsearch scope\n");
        fprintf(stderr, "\t-D binddn\t\tDN to bind as to perform searches\n");
        fprintf(stderr, "\t-w bindpasswd\t\tpassword for binddn\n");
        fprintf(stderr, "\t-W secretfile\t\tread password for binddn from file secretfile\n");
#if HAS_URI_SUPPORT
        fprintf(stderr, "\t-H URI\t\t\tLDAPURI (defaults to ldap://localhost)\n");
#endif
        fprintf(stderr, "\t-h server\t\tLDAP server (defaults to localhost)\n");
        fprintf(stderr, "\t-p port\t\t\tLDAP server port\n");
        fprintf(stderr, "\t-P\t\t\tpersistent LDAP connection\n");
#if defined(NETSCAPE_SSL)
        fprintf(stderr, "\t-E sslcertpath\t\tenable LDAP over SSL\n");
#endif
        fprintf(stderr, "\t-c timeout\t\tconnect timeout\n");
        fprintf(stderr, "\t-t timelimit\t\tsearch time limit\n");
        fprintf(stderr, "\t-R\t\t\tdo not follow referrals\n");
        fprintf(stderr, "\t-a never|always|search|find\n\t\t\t\twhen to dereference aliases\n");
#ifdef LDAP_VERSION3
        fprintf(stderr, "\t-v 2|3\t\t\tLDAP version\n");
        fprintf(stderr, "\t-Z\t\t\tTLS encrypt the LDAP connection, requires LDAP version 3\n");
#endif
        fprintf(stderr, "\t-d\t\t\tenable debug mode\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "\tIf no search filter is specified, then the dn <userattr>=user,basedn\n\twill be used (same as specifying a search filter of '<userattr>=',\n\tbut quicker as as there is no need to search for the user DN)\n\n");
        fprintf(stderr, "\tIf you need to bind as a user to perform searches then use the\n\t-D binddn -w bindpasswd or -D binddn -W secretfile options\n\n");
        exit(1);
    }
    /* On Windows ldap_start_tls_s is available starting from Windows XP,
     * so we need to bind at run-time with the function entry point
     */
#if _SQUID_WINDOWS_
    if (use_tls) {

        HMODULE WLDAP32Handle;

        WLDAP32Handle = GetModuleHandle("wldap32");
        if ((Win32_ldap_start_tls_s = (PFldap_start_tls_s) GetProcAddress(WLDAP32Handle, LDAP_START_TLS_S)) == NULL) {
            fprintf(stderr, PROGRAM_NAME ": ERROR: TLS (-Z) not supported on this platform.\n");
            exit(1);
        }
    }
#endif

    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        user = strtok(buf, " \r\n");
        passwd = strtok(NULL, "\r\n");

        if (!user) {
            printf("ERR Missing username\n");
            continue;
        }
        if (!passwd || !passwd[0]) {
            printf("ERR Missing password '%s'\n", user);
            continue;
        }
        rfc1738_unescape(user);
        rfc1738_unescape(passwd);
        if (!validUsername(user)) {
            printf("ERR No such user '%s':'%s'\n",user, passwd);
            continue;
        }
        tryagain = (ld != NULL);
recover:
        if (ld == NULL && persistent)
            ld = open_ldap_connection(ldapServer, port);
        if (checkLDAP(ld, user, passwd, ldapServer, port) != 0) {
            if (tryagain && squid_ldap_errno(ld) != LDAP_INVALID_CREDENTIALS) {
                tryagain = 0;
                ldap_unbind(ld);
                ld = NULL;
                goto recover;
            }
            printf("ERR %s\n", ldap_err2string(squid_ldap_errno(ld)));
        } else {
            printf("OK\n");
        }
        if (ld && (squid_ldap_errno(ld) != LDAP_SUCCESS && squid_ldap_errno(ld) != LDAP_INVALID_CREDENTIALS)) {
            ldap_unbind(ld);
            ld = NULL;
        }
    }
    if (ld)
        ldap_unbind(ld);
    return 0;
}