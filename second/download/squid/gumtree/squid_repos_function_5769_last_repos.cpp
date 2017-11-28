int
manage_request()
{
    char buf[HELPER_INPUT_BUFFER];
    uint8_t decoded[HELPER_INPUT_BUFFER];
    size_t decodedLen = 0;
    char helper_command[3];
    char *c;
    int status;
    int oversized = 0;
    char *ErrorMessage;
    static char cred[SSP_MAX_CRED_LEN + 1];
    BOOL Done = FALSE;

    do {
        if (fgets(buf, HELPER_INPUT_BUFFER, stdin))
            return 0;

        c = static_cast<char*>(memchr(buf, '\n', HELPER_INPUT_BUFFER));
        if (c) {
            if (oversized) {
                SEND("BH illegal request received");
                fprintf(stderr, "ERROR: Illegal request received: '%s'\n", buf);
                return 1;
            }
            *c = '\0';
        } else {
            fprintf(stderr, "No newline in '%s'\n", buf);
            oversized = 1;
        }
    } while (!c);

    if ((strlen(buf) > 3) && Negotiate_packet_debug_enabled) {
        if (!token_decode(&decodedLen, decoded, buf+3))
            return 1;
        strncpy(helper_command, buf, 2);
        debug("Got '%s' from Squid with data:\n", helper_command);
        hex_dump(reinterpret_cast<unsigned char*>(decoded), decodedLen);
    } else
        debug("Got '%s' from Squid\n", buf);

    if (memcmp(buf, "YR ", 3) == 0) {   /* refresh-request */
        /* figure out what we got */
        if (!decodedLen /* already decoded */ && !token_decode(&decodedLen, decoded, buf+3))
            return 1;
        if (decodedLen < sizeof(ntlmhdr)) {     /* decoding failure, return error */
            SEND("NA * Packet format error");
            return 1;
        }
        /* Obtain server blob against SSPI */
        c = (char *) SSP_MakeNegotiateBlob(decoded, decodedLen, &Done, &status, cred);

        if (status == SSP_OK) {
            if (Done) {
                lc(cred);   /* let's lowercase them for our convenience */
                have_serverblob = 0;
                Done = FALSE;
                if (Negotiate_packet_debug_enabled) {
                    if (!token_decode(&decodedLen, decoded, c))
                        return 1;
                    debug("sending 'AF' %s to squid with data:\n", cred);
                    if (c != NULL)
                        hex_dump(reinterpret_cast<unsigned char*>(decoded), decodedLen);
                    else
                        fprintf(stderr, "No data available.\n");
                    printf("AF %s %s\n", c, cred);
                } else
                    SEND3("AF %s %s", c, cred);
            } else {
                if (Negotiate_packet_debug_enabled) {
                    if (!token_decode(&decodedLen, decoded, c))
                        return 1;
                    debug("sending 'TT' to squid with data:\n");
                    hex_dump(reinterpret_cast<unsigned char*>(decoded), decodedLen);
                    printf("TT %s\n", c);
                } else {
                    SEND2("TT %s", c);
                }
                have_serverblob = 1;
            }
        } else
            SEND("BH can't obtain server blob");
        return 1;
    }
    if (memcmp(buf, "KK ", 3) == 0) {   /* authenticate-request */
        if (!have_serverblob) {
            SEND("BH invalid server blob");
            return 1;
        }
        /* figure out what we got */
        if (!decodedLen /* already decoded */ && !token_decode(&decodedLen, decoded, buf+3))
            return 1;
        if (decodedLen < sizeof(ntlmhdr)) {     /* decoding failure, return error */
            SEND("NA * Packet format error");
            return 1;
        }
        /* check against SSPI */
        c = (char *) SSP_ValidateNegotiateCredentials(decoded, decodedLen, &Done, &status, cred);

        if (status == SSP_ERROR) {
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                          FORMAT_MESSAGE_IGNORE_INSERTS,
                          NULL,
                          GetLastError(),
                          MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),    /* Default language */
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
            lc(cred);       /* let's lowercase them for our convenience */
            have_serverblob = 0;
            Done = FALSE;
            if (Negotiate_packet_debug_enabled) {
                if (!token_decode(&decodedLen, decoded, c))
                    return 1;
                debug("sending 'AF' %s to squid with data:\n", cred);
                if (c != NULL)
                    hex_dump(reinterpret_cast<unsigned char*>(decoded), decodedLen);
                else
                    fprintf(stderr, "No data available.\n");
                printf("AF %s %s\n", c, cred);
            } else {
                SEND3("AF %s %s", c, cred);
            }
            return 1;
        } else {
            if (Negotiate_packet_debug_enabled) {
                if (!token_decode(&decodedLen, decoded, c))
                    return 1;
                debug("sending 'TT' to squid with data:\n");
                hex_dump(reinterpret_cast<unsigned char*>(decoded), decodedLen);
                printf("TT %s\n", c);
            } else
                SEND2("TT %s", c);
            return 1;
        }

    } else {            /* not an auth-request */
        SEND("BH illegal request received");
        fprintf(stderr, "Illegal request received: '%s'\n", buf);
        return 1;
    }
    SEND("BH detected protocol error");
    return 1;
    /********* END ********/
}