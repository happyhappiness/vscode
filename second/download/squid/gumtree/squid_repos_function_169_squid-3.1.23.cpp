int
manage_request()
{
    char buf[BUFFER_SIZE];
    char helper_command[3];
    char *c, *decoded;
    int plen, status;
    int oversized = 0;
    char *ErrorMessage;
    static char cred[SSP_MAX_CRED_LEN + 1];
    BOOL Done = FALSE;

try_again:
    if (fgets(buf, BUFFER_SIZE, stdin) == NULL)
        return 0;

    c = memchr(buf, '\n', BUFFER_SIZE);		/* safer against overrun than strchr */
    if (c) {
        if (oversized) {
            helperfail("illegal request received");
            fprintf(stderr, "Illegal request received: '%s'\n", buf);
            return 1;
        }
        *c = '\0';
    } else {
        fprintf(stderr, "No newline in '%s'\n", buf);
        oversized = 1;
        goto try_again;
    }

    if ((strlen(buf) > 3) && Negotiate_packet_debug_enabled) {
        decoded = base64_decode(buf + 3);
        strncpy(helper_command, buf, 2);
        debug("Got '%s' from Squid with data:\n", helper_command);
        hex_dump(decoded, ((strlen(buf) - 3) * 3) / 4);
    } else
        debug("Got '%s' from Squid\n", buf);

    if (memcmp(buf, "YR ", 3) == 0) {	/* refresh-request */
        /* figure out what we got */
        decoded = base64_decode(buf + 3);
        /*  Note: we don't need to manage memory at this point, since
         *  base64_decode returns a pointer to static storage.
         */
        if (!decoded) {		/* decoding failure, return error */
            SEND("NA * Packet format error, couldn't base64-decode");
            return 1;
        }
        /* Obtain server blob against SSPI */
        plen = (strlen(buf) - 3) * 3 / 4;	/* we only need it here. Optimization */
        c = (char *) SSP_MakeNegotiateBlob(decoded, plen, &Done, &status, cred);

        if (status == SSP_OK) {
            if (Done) {
                lc(cred);	/* let's lowercase them for our convenience */
                have_serverblob = 0;
                Done = FALSE;
                if (Negotiate_packet_debug_enabled) {
                    decoded = base64_decode(c);
                    debug("sending 'AF' %s to squid with data:\n", cred);
                    if (c != NULL)
                        hex_dump(decoded, (strlen(c) * 3) / 4);
                    else
                        fprintf(stderr, "No data available.\n");
                    printf("AF %s %s\n", c, cred);
                } else
                    SEND3("AF %s %s", c, cred);
            } else {
                if (Negotiate_packet_debug_enabled) {
                    decoded = base64_decode(c);
                    debug("sending 'TT' to squid with data:\n");
                    hex_dump(decoded, (strlen(c) * 3) / 4);
                    printf("TT %s\n", c);
                } else {
                    SEND2("TT %s", c);
                }
                have_serverblob = 1;
            }
        } else
            helperfail("can't obtain server blob");
        return 1;
    }
    if (memcmp(buf, "KK ", 3) == 0) {	/* authenticate-request */
        if (!have_serverblob) {
            helperfail("invalid server blob");
            return 1;
        }
        /* figure out what we got */
        decoded = base64_decode(buf + 3);
        /*  Note: we don't need to manage memory at this point, since
         *  base64_decode returns a pointer to static storage.
         */
        if (!decoded) {		/* decoding failure, return error */
            SEND("NA * Packet format error, couldn't base64-decode");
            return 1;
        }
        /* check against SSPI */
        plen = (strlen(buf) - 3) * 3 / 4;	/* we only need it here. Optimization */
        c = (char *) SSP_ValidateNegotiateCredentials(decoded, plen, &Done, &status, cred);

        if (status == SSP_ERROR) {
#if FAIL_DEBUG
            fail_debug_enabled = 1;
#endif
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                          FORMAT_MESSAGE_IGNORE_INSERTS,
                          NULL,
                          GetLastError(),
                          MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),	/* Default language */
                          (LPTSTR) & ErrorMessage,
                          0,
                          NULL);
            if (ErrorMessage[strlen(ErrorMessage) - 1] == '\n')
                ErrorMessage[strlen(ErrorMessage) - 1] = '\0';
            if (ErrorMessage[strlen(ErrorMessage) - 1] == '\r')
                ErrorMessage[strlen(ErrorMessage) - 1] = '\0';
            SEND2("NA * %s", ErrorMessage);
            LocalFree(ErrorMessage);
            return 1;
        }
        if (Done) {
            lc(cred);		/* let's lowercase them for our convenience */
            have_serverblob = 0;
            Done = FALSE;
            if (Negotiate_packet_debug_enabled) {
                decoded = base64_decode(c);
                debug("sending 'AF' %s to squid with data:\n", cred);
                if (c != NULL)
                    hex_dump(decoded, (strlen(c) * 3) / 4);
                else
                    fprintf(stderr, "No data available.\n");
                printf("AF %s %s\n", c, cred);
            } else {
                SEND3("AF %s %s", c, cred);
            }
            return 1;
        } else {
            if (Negotiate_packet_debug_enabled) {
                decoded = base64_decode(c);
                debug("sending 'TT' to squid with data:\n");
                hex_dump(decoded, (strlen(c) * 3) / 4);
                printf("TT %s\n", c);
            } else
                SEND2("TT %s", c);
            return 1;
        }

    } else {			/* not an auth-request */
        helperfail("illegal request received");
        fprintf(stderr, "Illegal request received: '%s'\n", buf);
        return 1;
    }
    helperfail("detected protocol error");
    return 1;
    /********* END ********/
}