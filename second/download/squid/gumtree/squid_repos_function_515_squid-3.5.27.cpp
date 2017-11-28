int
LDAPArguments(int argc, char **argv)
{
    setbuf(stdout, NULL);

    while (argc > 1 && argv[1][0] == '-') {
        const char *value = "";
        char option = argv[1][1];
        switch (option) {
        case 'P':
        case 'R':
        case 'z':
        case 'Z':
        case 'g':
        case 'e':
        case 'S':
        case 'n':
        case 'd':
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
            return 1;
#endif
        /* Fall thru to -h */
        case 'h':
            if (ldapServer) {
                int len = strlen(ldapServer) + 1 + strlen(value) + 1;
                char *newhost = static_cast<char*>(xmalloc(len));
                snprintf(newhost, len, "%s %s", ldapServer, value);
                free(ldapServer);
                ldapServer = newhost;
            } else {
                ldapServer = xstrdup(value);
            }
            break;
        case 'A':
            passattr = value;
            break;
        case 'e':
            encrpass = 1;
            break;
        case 'l':
            delimiter = value;
            break;
        case 'b':
            userbasedn = value;
            break;
        case 'F':
            usersearchfilter = value;
            break;
        case 'u':
            userdnattr = value;
            break;
        case 's':
            if (strcmp(value, "base") == 0)
                searchscope = LDAP_SCOPE_BASE;
            else if (strcmp(value, "one") == 0)
                searchscope = LDAP_SCOPE_ONELEVEL;
            else if (strcmp(value, "sub") == 0)
                searchscope = LDAP_SCOPE_SUBTREE;
            else {
                fprintf(stderr, PROGRAM_NAME " ERROR: Unknown search scope '%s'\n", value);
                return 1;
            }
            break;
        case 'S':
#if defined(NETSCAPE_SSL)
            sslpath = value;
            if (port == LDAP_PORT)
                port = LDAPS_PORT;
#else
            fprintf(stderr, PROGRAM_NAME " ERROR: -E unsupported with this LDAP library\n");
            return 1;
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
                fprintf(stderr, PROGRAM_NAME " ERROR: Unknown alias dereference method '%s'\n", value);
                return 1;
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
                return 1;
            }
            break;
        case 'Z':
            if (version == LDAP_VERSION2) {
                fprintf(stderr, "TLS (-Z) is incompatible with version %d\n",
                        version);
                return 1;
            }
            version = LDAP_VERSION3;
            use_tls = 1;
            break;
#endif
        case 'd':
            debug_enabled = 1;
            break;
        case 'E':
            strip_nt_domain = 1;
            break;
        case 'n':
            edir_universal_passwd = 1;
            break;
        default:
            fprintf(stderr, PROGRAM_NAME " ERROR: Unknown command line option '%c'\n", option);
            return 1;
        }
    }

    while (argc > 1) {
        char *value = argv[1];
        if (ldapServer) {
            int len = strlen(ldapServer) + 1 + strlen(value) + 1;
            char *newhost = static_cast<char*>(xmalloc(len));
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
        ldapServer = (char *) "localhost";

    if (!userbasedn || !((passattr != NULL) || (edir_universal_passwd && usersearchfilter && version == LDAP_VERSION3 && use_tls))) {
        fprintf(stderr, "Usage: " PROGRAM_NAME " -b basedn -f filter [options] ldap_server_name\n\n");
        fprintf(stderr, "\t-A password attribute(REQUIRED)\t\tUser attribute that contains the password\n");
        fprintf(stderr, "\t-l password realm delimiter(REQUIRED)\tCharater(s) that devides the password attribute\n\t\t\t\t\t\tin realm and password tokens, default ':' realm:password\n");
        fprintf(stderr, "\t-b basedn (REQUIRED)\t\t\tbase dn under where to search for users\n");
        fprintf(stderr, "\t-e Encrypted passwords(REQUIRED)\tPassword are stored encrypted using HHA1\n");
        fprintf(stderr, "\t-F filter\t\t\t\tuser search filter pattern. %%s = login\n");
        fprintf(stderr, "\t-u attribute\t\t\t\tattribute to use in combination with the basedn to create the user DN\n");
        fprintf(stderr, "\t-s base|one|sub\t\t\t\tsearch scope\n");
        fprintf(stderr, "\t-D binddn\t\t\t\tDN to bind as to perform searches\n");
        fprintf(stderr, "\t-w bindpasswd\t\t\t\tpassword for binddn\n");
        fprintf(stderr, "\t-W secretfile\t\t\t\tread password for binddn from file secretfile\n");
#if HAS_URI_SUPPORT
        fprintf(stderr, "\t-H URI\t\t\t\t\tLDAPURI (defaults to ldap://localhost)\n");
#endif
        fprintf(stderr, "\t-h server\t\t\t\tLDAP server (defaults to localhost)\n");
        fprintf(stderr, "\t-p port\t\t\t\t\tLDAP server port (defaults to %d)\n", LDAP_PORT);
        fprintf(stderr, "\t-P\t\t\t\t\tpersistent LDAP connection\n");
#if defined(NETSCAPE_SSL)
        fprintf(stderr, "\t-E sslcertpath\t\t\t\tenable LDAP over SSL\n");
#endif
        fprintf(stderr, "\t-c timeout\t\t\t\tconnect timeout\n");
        fprintf(stderr, "\t-t timelimit\t\t\t\tsearch time limit\n");
        fprintf(stderr, "\t-R\t\t\t\t\tdo not follow referrals\n");
        fprintf(stderr, "\t-a never|always|search|find\t\twhen to dereference aliases\n");
#ifdef LDAP_VERSION3
        fprintf(stderr, "\t-v 2|3\t\t\t\t\tLDAP version\n");
        fprintf(stderr, "\t-Z\t\t\t\t\tTLS encrypt the LDAP connection, requires\n\t\t\t\tLDAP version 3\n");
#endif
        fprintf(stderr, "\t-S\t\t\t\t\tStrip NT domain from usernames\n");
        fprintf(stderr, "\t-n\t\t\t\t\tGet an eDirectory Universal Password from Novell NMAS\n\t\t\t\t\t\t(requires bind credentials, version 3, TLS, and a search filter)\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "\tIf you need to bind as a user to perform searches then use the\n\t-D binddn -w bindpasswd or -D binddn -W secretfile options\n\n");
        return -1;
    }
    return 0;
}