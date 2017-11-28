int
manage_request()
{
    ntlmhdr *fast_header;
    char buf[HELPER_INPUT_BUFFER];
    char decoded[HELPER_INPUT_BUFFER];
    int decodedLen;
    char helper_command[3];
    int oversized = 0;
    char * ErrorMessage;
    static ntlm_negotiate local_nego;
    char domain[DNLEN+1];
    char user[UNLEN+1];

    /* NP: for some reason this helper sometimes needs to accept
     * from clients that send no negotiate packet. */
    if (memcpy(local_nego.hdr.signature, "NTLMSSP", 8) != 0) {
        memset(&local_nego, 0, sizeof(ntlm_negotiate)); /* reset */
        memcpy(local_nego.hdr.signature, "NTLMSSP", 8);     /* set the signature */
        local_nego.hdr.type = le32toh(NTLM_NEGOTIATE);      /* this is a challenge */
        local_nego.flags = le32toh(NTLM_NEGOTIATE_ALWAYS_SIGN |
                                   NTLM_NEGOTIATE_USE_NTLM |
                                   NTLM_NEGOTIATE_USE_LM |
                                   NTLM_NEGOTIATE_ASCII );
    }

    do {
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            return 0;

        char *c = static_cast<char*>(memchr(buf, '\n', sizeof(buf)));
        if (c) {
            if (oversized) {
                helperfail("messge=\"illegal request received\"");
                fprintf(stderr, "Illegal request received: '%s'\n", buf);
                return 1;
            }
            *c = '\0';
        } else {
            fprintf(stderr, "No newline in '%s'\n", buf);
            oversized = 1;
            continue;
        }
    } while (false);

    if ((strlen(buf) > 3) && NTLM_packet_debug_enabled) {
        decodedLen = base64_decode(decoded, sizeof(decoded), buf+3);
        strncpy(helper_command, buf, 2);
        debug("Got '%s' from Squid with data:\n", helper_command);
        hex_dump(reinterpret_cast<unsigned char*>(decoded), decodedLen);
    } else
        debug("Got '%s' from Squid\n", buf);
    if (memcmp(buf, "YR", 2) == 0) {    /* refresh-request */
        /* figure out what we got */
        if (strlen(buf) > 3)
            decodedLen = base64_decode(decoded, sizeof(decoded), buf+3);
        else {
            debug("Negotiate packet not supplied - self generated\n");
            memcpy(decoded, &local_nego, sizeof(local_nego));
            decodedLen = sizeof(local_nego);
        }
        if ((size_t)decodedLen < sizeof(ntlmhdr)) {     /* decoding failure, return error */
            SEND_ERR("message=\"Packet format error, couldn't base64-decode\"");
            return 1;
        }
        /* fast-track-decode request type. */
        fast_header = (struct _ntlmhdr *) decoded;

        /* sanity-check: it IS a NTLMSSP packet, isn't it? */
        if (ntlm_validate_packet(fast_header, NTLM_ANY) != NTLM_ERR_NONE) {
            SEND_ERR("message=\"Broken authentication packet\"");
            return 1;
        }
        switch (fast_header->type) {
        case NTLM_NEGOTIATE: {
            /* Obtain challenge against SSPI */
            debug("attempting SSPI challenge retrieval\n");
            char *c = (char *) SSP_MakeChallenge((ntlm_negotiate *) decoded, decodedLen);
            if (c) {
                SEND_TT(c);
                if (NTLM_packet_debug_enabled) {
                    decodedLen = base64_decode(decoded, sizeof(decoded), c);
                    debug("send 'TT' to squid with data:\n");
                    hex_dump(reinterpret_cast<unsigned char*>(decoded), decodedLen);
                    if (NTLM_LocalCall) {
                        debug("NTLM Local Call detected\n");
                    }
                }
                have_challenge = 1;
            } else
                helperfail("message=\"can't obtain challenge\"");

            return 1;
        }
        /* notreached */
        case NTLM_CHALLENGE:
            SEND_ERR("message=\"Got a challenge. We refuse to have our authority disputed\"");
            return 1;
        /* notreached */
        case NTLM_AUTHENTICATE:
            SEND_ERR("message=\"Got authentication request instead of negotiate request\"");
            return 1;
        /* notreached */
        default:
            helperfail("message=\"unknown refresh-request packet type\"");
            return 1;
        }
        return 1;
    }
    if (memcmp(buf, "KK ", 3) == 0) {   /* authenticate-request */
        if (!have_challenge) {
            helperfail("message=\"invalid challenge\"");
            return 1;
        }
        /* figure out what we got */
        decodedLen = base64_decode(decoded, sizeof(decoded), buf+3);

        if ((size_t)decodedLen < sizeof(ntlmhdr)) {     /* decoding failure, return error */
            SEND_ERR("message=\"Packet format error, couldn't base64-decode\"");
            return 1;
        }
        /* fast-track-decode request type. */
        fast_header = (struct _ntlmhdr *) decoded;

        /* sanity-check: it IS a NTLMSSP packet, isn't it? */
        if (ntlm_validate_packet(fast_header, NTLM_ANY) != NTLM_ERR_NONE) {
            SEND_ERR("message=\"Broken authentication packet\"");
            return 1;
        }
        switch (fast_header->type) {
        case NTLM_NEGOTIATE:
            SEND_ERR("message=\"Invalid negotiation request received\"");
            return 1;
        /* notreached */
        case NTLM_CHALLENGE:
            SEND_ERR("message=\"Got a challenge. We refuse to have our authority disputed\"");
            return 1;
        /* notreached */
        case NTLM_AUTHENTICATE: {
            /* check against SSPI */
            int err = ntlm_check_auth((ntlm_authenticate *) decoded, user, domain, decodedLen);
            have_challenge = 0;
            if (err != NTLM_ERR_NONE) {
#if FAIL_DEBUG
                fail_debug_enabled =1;
#endif
                switch (err) {
                case NTLM_ERR_NONE:
                    break;
                case NTLM_BAD_NTGROUP:
                    SEND_ERR("message=\"Incorrect Group Membership\"");
                    return 1;
                case NTLM_BAD_REQUEST:
                    SEND_ERR("message=\"Incorrect Request Format\"");
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
                    SEND_ERR(ErrorMessage); // TODO update to new syntax
                    LocalFree(ErrorMessage);
                    return 1;
                default:
                    SEND_ERR("message=\"Unknown Error\"");
                    return 1;
                }
            }
            /* let's lowercase them for our convenience */
            lc(domain);
            lc(user);
            fprintf(stdout, "OK user=\"%s\\%s\"", domain, user);
            return 1;
        }
        default:
            helperfail("message=\"unknown authentication packet type\"");
            return 1;
        }
        return 1;
    } else {    /* not an auth-request */
        helperfail("message=\"illegal request received\"");
        fprintf(stderr, "Illegal request received: '%s'\n", buf);
        return 1;
    }
    helperfail("message=\"detected protocol error\"");
    return 1;
    /********* END ********/
}