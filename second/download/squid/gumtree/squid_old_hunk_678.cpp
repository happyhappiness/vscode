    const char *ch;
    char *ch2, *cred = NULL;

    if (fgets(buf, NTLM_BLOB_BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "fgets() failed! dying..... errno=%d (%s)\n", errno,
                strerror(errno));
        exit(1);		/* BIIG buffer */
    }
    debug("managing request\n");
    ch2 = (char*)memchr(buf, '\n', NTLM_BLOB_BUFFER_SIZE);	/* safer against overrun than strchr */
    if (ch2) {
        *ch2 = '\0';		/* terminate the string at newline. */
        ch = ch2;
    }
    debug("ntlm authenticator. Got '%s' from Squid\n", buf);

    if (memcmp(buf, "KK ", 3) == 0) {	/* authenticate-request */
        /* figure out what we got */
        int decodedLen = base64_decode(decoded, sizeof(decoded), buf+3);

        if ((size_t)decodedLen < sizeof(ntlmhdr)) {	/* decoding failure, return error */
            SEND("NA Packet format error, couldn't base64-decode");
            return;
        }
        /* fast-track-decode request type. */
        fast_header = (ntlmhdr *) decoded;

