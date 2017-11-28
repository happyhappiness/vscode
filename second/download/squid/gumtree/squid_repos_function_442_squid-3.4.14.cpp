int
main(int argc, char *argv[])
{
    pam_handle_t *pamh = NULL;
    int retval = PAM_SUCCESS;
    char *user;
    char *password_buf;
    char buf[HELPER_INPUT_BUFFER];
    time_t pamh_created = 0;
    int ttl = DEFAULT_SQUID_PAM_TTL;
    const char *service = DEFAULT_SQUID_PAM_SERVICE;
    int no_acct_mgmt = 0;
    int no_realm = 0;

    /* make standard output line buffered */
    setvbuf(stdout, NULL, _IOLBF, 0);

    while (1) {
        int ch = getopt(argc, argv, "1n:t:or");
        switch (ch) {
        case -1:
            goto start;
        case 'n':
            service = optarg;
            break;
        case 't':
            ttl = atoi(optarg);
            break;
        case '1':
            ttl = 0;
            break;
        case 'o':
            no_acct_mgmt = 1;
            break;
        case 'r':
            no_realm = 1;
            break;
        default:
            fprintf(stderr, "FATAL: Unknown getopt value '%c'\n", ch);
            usage(argv[0]);
            exit(1);
        }
    }
start:
    if (optind < argc) {
        fprintf(stderr, "FATAL: Unknown option '%s'\n", argv[optind]);
        usage(argv[0]);
        exit(1);
    }

    while (fgets(buf, HELPER_INPUT_BUFFER, stdin)) {
        user = buf;
        password_buf = strchr(buf, '\n');
        if (!password_buf) {
            debug("ERROR: %s: Unexpected input '%s'\n", argv[0], buf);
            goto error;
        }
        *password_buf = '\0';
        password_buf = strchr(buf, ' ');
        if (!password_buf) {
            debug("ERROR: %s: Unexpected input '%s'\n", argv[0], buf);
            goto error;
        }
        *password_buf = '\0';
        ++password_buf;
        rfc1738_unescape(user);
        rfc1738_unescape(password_buf);
        conv.appdata_ptr = (char *) password_buf;	/* from buf above. not allocated */

        if (no_realm) {
            /* Remove DOMAIN\.. and ...@domain from the user name in case the user
             * thought this was an NTLM or Negotiate authentication popup box
             */
            char * user_ptr = strchr(user, '@');
            if (user_ptr) *user_ptr = 0;
            else {
                user_ptr = strchr(user, '\\');
                if (user_ptr) user = user_ptr + 1;
            }
        }

#if _SQUID_SOLARIS_
        /* Workaround for Solaris 2.6 where the PAM library is broken
         * and does not pass appdata_ptr to the conversation routine
         */
        password = password_buf;
#endif
        if (ttl == 0) {
            /* Create PAM connection */
            retval = pam_start(service, user, &conv, &pamh);
            if (retval != PAM_SUCCESS) {
                debug("ERROR: failed to create PAM authenticator\n");
                goto error;
            }
        } else if (!pamh || (time(NULL) - pamh_created) >= ttl || pamh_created > time(NULL)) {
            /* Close previous PAM connection */
            if (pamh) {
                retval = pam_end(pamh, retval);
                if (retval != PAM_SUCCESS) {
                    debug("WARNING: failed to release PAM authenticator\n");
                }
                pamh = NULL;
            }
            /* Initialize persistent PAM connection */
            retval = pam_start(service, "squid@", &conv, &pamh);
            if (retval != PAM_SUCCESS) {
                debug("ERROR: failed to create PAM authenticator\n");
                goto error;
            }
            pamh_created = time(NULL);
        }
        /* Authentication */
        retval = PAM_SUCCESS;
        if (ttl != 0) {
            retval = pam_set_item(pamh, PAM_USER, user);
            if (retval == PAM_SUCCESS)
                retval = pam_set_item(pamh, PAM_CONV, &conv);
        }
        if (retval == PAM_SUCCESS)
            retval = pam_authenticate(pamh, 0);
        if (retval == PAM_SUCCESS && !no_acct_mgmt)
            retval = pam_acct_mgmt(pamh, 0);
        if (retval == PAM_SUCCESS) {
            SEND_OK("");
        } else {
error:
            SEND_ERR("");
        }
        /* cleanup */
        retval = PAM_SUCCESS;
#if defined(PAM_AUTHTOK)
        if (ttl != 0 && pamh) {
            retval = pam_set_item(pamh, PAM_AUTHTOK, NULL);
        }
#endif
        if (pamh && (ttl == 0 || retval != PAM_SUCCESS)) {
            retval = pam_end(pamh, retval);
            if (retval != PAM_SUCCESS) {
                debug("WARNING: failed to release PAM authenticator\n");
            }
            pamh = NULL;
        }
    }

    if (pamh) {
        retval = pam_end(pamh, retval);
        if (retval != PAM_SUCCESS) {
            pamh = NULL;
            debug("ERROR: failed to release PAM authenticator\n");
        }
    }
    return 0;
}