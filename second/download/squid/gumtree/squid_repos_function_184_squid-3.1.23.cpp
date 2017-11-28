int
manage_request()
{
    ntlmhdr *fast_header;
    char buf[BUFFER_SIZE];
    char helper_command[3];
    char *c, *decoded, *cred;
    int plen;
    int oversized = 0;
    char * ErrorMessage;

try_again:
    if (fgets(buf, BUFFER_SIZE, stdin) == NULL)
        return 0;

    c = memchr(buf, '\n', BUFFER_SIZE);	/* safer against overrun than strchr */
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
    if ((strlen(buf) > 3) && NTLM_packet_debug_enabled) {
        decoded = base64_decode(buf + 3);
        strncpy(helper_command, buf, 2);
        debug("Got '%s' from Squid with data:\n", helper_command);
        hex_dump(decoded, ((strlen(buf) - 3) * 3) / 4);
    } else
        debug("Got '%s' from Squid\n", buf);
    if (memcmp(buf, "YR", 2) == 0) {	/* refresh-request */
        /* figure out what we got */
        if (strlen(buf) > 3)
            decoded = base64_decode(buf + 3);
        else
            decoded = base64_decode(ntlm_make_negotiate());
        /* Note: we don't need to manage memory at this point, since
         *  base64_decode returns a pointer to static storage.
         */
        if (!decoded) {		/* decoding failure, return error */
            SEND("NA Packet format error, couldn't base64-decode");
            return 1;
        }
        /* fast-track-decode request type. */
        fast_header = (struct _ntlmhdr *) decoded;

        /* sanity-check: it IS a NTLMSSP packet, isn't it? */
        if (memcmp(fast_header->signature, "NTLMSSP", 8) != 0) {
            SEND("NA Broken authentication packet");
            return 1;
        }
        switch (fast_header->type) {
        case NTLM_NEGOTIATE:
            /* Obtain challenge against SSPI */
            if (strlen(buf) > 3)
                plen = (strlen(buf) - 3) * 3 / 4;		/* we only need it here. Optimization */
            else
                plen = NEGOTIATE_LENGTH;
            if ((c = (char *) obtain_challenge((ntlm_negotiate *) decoded, plen)) != NULL ) {
                if (NTLM_packet_debug_enabled) {
                    printf("TT %s\n",c);
                    decoded = base64_decode(c);
                    debug("sending 'TT' to squid with data:\n");
                    hex_dump(decoded, (strlen(c) * 3) / 4);
                    if (NTLM_LocalCall)
                        debug("NTLM Local Call detected\n");
                } else {
                    SEND2("TT %s", c);
                }
                have_challenge = 1;
            } else
                helperfail("can't obtain challenge");
            return 1;
            /* notreached */
        case NTLM_CHALLENGE:
            SEND
            ("NA Got a challenge. We refuse to have our authority disputed");
            return 1;
            /* notreached */
        case NTLM_AUTHENTICATE:
            SEND("NA Got authentication request instead of negotiate request");
            return 1;
            /* notreached */
        default:
            helperfail("unknown refresh-request packet type");
            return 1;
        }
        return 1;
    }
    if (memcmp(buf, "KK ", 3) == 0) {	/* authenticate-request */
        if (!have_challenge) {
            helperfail("invalid challenge");
            return 1;
        }
        /* figure out what we got */
        decoded = base64_decode(buf + 3);
        /* Note: we don't need to manage memory at this point, since
         *  base64_decode returns a pointer to static storage.
         */

        if (!decoded) {		/* decoding failure, return error */
            SEND("NA Packet format error, couldn't base64-decode");
            return 1;
        }
        /* fast-track-decode request type. */
        fast_header = (struct _ntlmhdr *) decoded;

        /* sanity-check: it IS a NTLMSSP packet, isn't it? */
        if (memcmp(fast_header->signature, "NTLMSSP", 8) != 0) {
            SEND("NA Broken authentication packet");
            return 1;
        }
        switch (fast_header->type) {
        case NTLM_NEGOTIATE:
            SEND("NA Invalid negotiation request received");
            return 1;
            /* notreached */
        case NTLM_CHALLENGE:
            SEND
            ("NA Got a challenge. We refuse to have our authority disputed");
            return 1;
            /* notreached */
        case NTLM_AUTHENTICATE:
            /* check against SSPI */
            plen = (strlen(buf) - 3) * 3 / 4;		/* we only need it here. Optimization */
            cred = ntlm_check_auth((ntlm_authenticate *) decoded, plen);
            have_challenge = 0;
            if (cred == NULL) {
#if FAIL_DEBUG
                fail_debug_enabled =1;
#endif
                switch (ntlm_errno) {
                case NTLM_BAD_NTGROUP:
                    SEND("NA Incorrect Group Membership");
                    return 1;
                case NTLM_BAD_REQUEST:
                    SEND("NA Incorrect Request Format");
                    return 1;
                case NTLM_SSPI_ERROR:
                    FormatMessage(
                        FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        GetLastError(),
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                        (LPTSTR) &ErrorMessage,
                        0,
                        NULL);
                    if (ErrorMessage[strlen(ErrorMessage) - 1] == '\n')
                        ErrorMessage[strlen(ErrorMessage) - 1] = '\0';
                    if (ErrorMessage[strlen(ErrorMessage) - 1] == '\r')
                        ErrorMessage[strlen(ErrorMessage) - 1] = '\0';
                    SEND2("NA %s", ErrorMessage);
                    LocalFree(ErrorMessage);
                    return 1;
                default:
                    SEND("NA Unknown Error");
                    return 1;
                }
            }
            lc(cred);		/* let's lowercase them for our convenience */
            SEND2("AF %s", cred);
            return 1;
        default:
            helperfail("unknown authentication packet type");
            return 1;
        }
        return 1;
    } else {	/* not an auth-request */
        helperfail("illegal request received");
        fprintf(stderr, "Illegal request received: '%s'\n", buf);
        return 1;
    }
    helperfail("detected protocol error");
    return 1;
    /********* END ********/
}