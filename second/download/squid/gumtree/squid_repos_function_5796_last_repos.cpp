static int
processingLoop(FILE *FDKIN, FILE *FDKOUT, FILE *FDNIN, FILE *FDNOUT)
{
    char buf[MAX_AUTHTOKEN_LEN];
    char tbuff[MAX_AUTHTOKEN_LEN];
    char buff[MAX_AUTHTOKEN_LEN+2];
    char *c;
    int length;
    uint8_t *token = NULL;

    while (1) {
        if (fgets(buf, sizeof(buf) - 1, stdin) == NULL) {
            xfree(token);
            if (ferror(stdin)) {
                if (debug_enabled)
                    fprintf(stderr,
                            "%s| %s: fgets() failed! dying..... errno=%d (%s)\n",
                            LogTime(), PROGRAM, ferror(stdin),
                            strerror(ferror(stdin)));

                fprintf(stdout, "BH input error\n");
                return 1;        /* BIIG buffer */
            }
            fprintf(stdout, "BH input error\n");
            return 0;
        }
        c = static_cast<char*>(memchr(buf, '\n', sizeof(buf) - 1));
        if (c) {
            *c = '\0';
            length = c - buf;
            if (debug_enabled)
                fprintf(stderr, "%s| %s: Got '%s' from squid (length: %d).\n",
                        LogTime(), PROGRAM, buf, length);
        } else {
            if (debug_enabled)
                fprintf(stderr, "%s| %s: Oversized message\n", LogTime(),
                        PROGRAM);
            fprintf(stdout, "BH Oversized message\n");
            continue;
        }

        if (buf[0] == '\0') {
            if (debug_enabled)
                fprintf(stderr, "%s| %s: Invalid request\n", LogTime(),
                        PROGRAM);
            fprintf(stdout, "BH Invalid request\n");
            continue;
        }
        if (strlen(buf) < 2) {
            if (debug_enabled)
                fprintf(stderr, "%s| %s: Invalid request [%s]\n", LogTime(),
                        PROGRAM, buf);
            fprintf(stdout, "BH Invalid request\n");
            continue;
        }
        if (!strncmp(buf, "QQ", 2)) {
            fprintf(stdout, "BH quit command\n");
            xfree(token);
            return 0;
        }
        if (strncmp(buf, "YR", 2) && strncmp(buf, "KK", 2)) {
            if (debug_enabled)
                fprintf(stderr, "%s| %s: Invalid request [%s]\n", LogTime(),
                        PROGRAM, buf);
            fprintf(stdout, "BH Invalid request\n");
            continue;
        }
        if (strlen(buf) <= 3) {
            if (debug_enabled)
                fprintf(stderr, "%s| %s: Invalid negotiate request [%s]\n",
                        LogTime(), PROGRAM, buf);
            fprintf(stdout, "BH Invalid negotiate request\n");
            continue;
        }
        length = BASE64_DECODE_LENGTH(strlen(buf+3));
        if (debug_enabled)
            fprintf(stderr, "%s| %s: Decode '%s' (decoded length: %d).\n",
                    LogTime(), PROGRAM, buf + 3, (int) length);

        safe_free(token);
        if (!(token = static_cast<uint8_t *>(xmalloc(length)))) {
            fprintf(stderr, "%s| %s: Error allocating memory for token\n", LogTime(), PROGRAM);
            return 1;
        }

        struct base64_decode_ctx ctx;
        base64_decode_init(&ctx);
        size_t dstLen = 0;
        if (!base64_decode_update(&ctx, &dstLen, token, strlen(buf+3), reinterpret_cast<const uint8_t*>(buf+3)) ||
                !base64_decode_final(&ctx)) {
            if (debug_enabled)
                fprintf(stderr, "%s| %s: Invalid base64 token [%s]\n", LogTime(), PROGRAM, buf+3);
            fprintf(stdout, "BH Invalid negotiate request token\n");
            continue;
        }
        length = dstLen;
        token[dstLen] = '\0';

        if ((static_cast<size_t>(length) >= sizeof(ntlmProtocol) + 1) &&
                (!memcmp(token, ntlmProtocol, sizeof ntlmProtocol))) {
            if (debug_enabled)
                fprintf(stderr, "%s| %s: received type %d NTLM token\n",
                        LogTime(), PROGRAM, (int) *((unsigned char *) token +
                                                    sizeof ntlmProtocol));
            fprintf(FDNIN, "%s\n",buf);
            if (fgets(tbuff, sizeof(tbuff) - 1, FDNOUT) == NULL) {
                xfree(token);
                if (ferror(FDNOUT)) {
                    fprintf(stderr,
                            "fgets() failed! dying..... errno=%d (%s)\n",
                            ferror(FDNOUT), strerror(ferror(FDNOUT)));
                    return 1;
                }
                fprintf(stderr, "%s| %s: Error reading NTLM helper response\n",
                        LogTime(), PROGRAM);
                return 0;
            }
            /*
             * Need to translate NTLM reply to Negotiate reply:
             *  AF user => AF blob user
             *  NA reason => NA blob reason
             *  Set blob to '='
             */
            if (strlen(tbuff) >= 3 && (!strncmp(tbuff,"AF ",3) || !strncmp(tbuff,"NA ",3))) {
                strncpy(buff,tbuff,3);
                buff[3]='=';
                for (unsigned int i=2; i<=strlen(tbuff); ++i)
                    buff[i+2] = tbuff[i];
            } else {
                strcpy(buff,tbuff);
            }
        } else {
            if (debug_enabled)
                fprintf(stderr, "%s| %s: received Kerberos token\n",
                        LogTime(), PROGRAM);

            fprintf(FDKIN, "%s\n",buf);
            if (fgets(buff, sizeof(buff) - 1, FDKOUT) == NULL) {
                xfree(token);
                if (ferror(FDKOUT)) {
                    fprintf(stderr,
                            "fgets() failed! dying..... errno=%d (%s)\n",
                            ferror(FDKOUT), strerror(ferror(FDKOUT)));
                    return 1;
                }
                fprintf(stderr, "%s| %s: Error reading Kerberos helper response\n",
                        LogTime(), PROGRAM);
                return 0;
            }
        }
        fprintf(stdout,"%s",buff);
        if (debug_enabled)
            fprintf(stderr, "%s| %s: Return '%s'\n",
                    LogTime(), PROGRAM, buff);
    }

    xfree(token);
    return 1;
}