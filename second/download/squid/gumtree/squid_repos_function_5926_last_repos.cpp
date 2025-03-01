int
main(int argc, char *argv[])
{
    char buf[HELPER_INPUT_BUFFER];
    int buflen = 0;
    uint8_t decodedBuf[HELPER_INPUT_BUFFER];
    int decodedLen;
    char user[NTLM_MAX_FIELD_LENGTH], domain[NTLM_MAX_FIELD_LENGTH];
    char *p;
    char helper_command[3];
    int len;

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    my_program_name = argv[0];

    process_options(argc, argv);

    debug("%s " VERSION " " SQUID_BUILD_INFO " starting up...\n", my_program_name);

    while (fgets(buf, HELPER_INPUT_BUFFER, stdin) != NULL) {
        user[0] = '\0';     /*no user code */
        domain[0] = '\0';       /*no domain code */

        if ((p = strchr(buf, '\n')) != NULL)
            *p = '\0';      /* strip \n */
        buflen = strlen(buf);   /* keep this so we only scan the buffer for \0 once per loop */
        ntlmhdr *packet;
        struct base64_decode_ctx ctx;
        base64_decode_init(&ctx);
        size_t dstLen = 0;
        if (buflen > 3 &&
                base64_decode_update(&ctx, &dstLen, decodedBuf, buflen-3, reinterpret_cast<const uint8_t*>(buf+3)) &&
                base64_decode_final(&ctx)) {
            decodedLen = dstLen;
            packet = (ntlmhdr*)decodedBuf;
        } else {
            packet = NULL;
            decodedLen = 0;
        }

        if (buflen > 3 && NTLM_packet_debug_enabled) {
            strncpy(helper_command, buf, 2);
            helper_command[2] = '\0';
            debug("Got '%s' from Squid with data:\n", helper_command);
            hex_dump((unsigned char *)decodedBuf, decodedLen);
        } else
            debug("Got '%s' from Squid\n", buf);

        if (strncmp(buf, "YR", 2) == 0) {
            char nonce[NTLM_NONCE_LEN];
            ntlm_challenge chal;
            ntlm_make_nonce(nonce);
            if (buflen > 3 && packet) {
                ntlm_negotiate *nego = (ntlm_negotiate *)packet;
                ntlm_make_challenge(&chal, authenticate_ntlm_domain, NULL, nonce, NTLM_NONCE_LEN, nego->flags);
            } else {
                ntlm_make_challenge(&chal, authenticate_ntlm_domain, NULL, nonce, NTLM_NONCE_LEN, NTLM_NEGOTIATE_ASCII);
            }
            // TODO: find out what this context means, and why only the fake auth helper contains it.
            chal.context_high = htole32(0x003a<<16);

            len = sizeof(chal) - sizeof(chal.payload) + le16toh(chal.target.maxlen);

            struct base64_encode_ctx eCtx;
            base64_encode_init(&eCtx);
            uint8_t *data = (uint8_t*)xcalloc(base64_encode_len(len), 1);
            size_t blen = base64_encode_update(&eCtx, data, len, reinterpret_cast<uint8_t*>(&chal));
            blen += base64_encode_final(&eCtx, data+blen);
            if (NTLM_packet_debug_enabled) {
                printf("TT %.*s\n", (int)blen, data);
                debug("sending 'TT' to squid with data:\n");
                hex_dump((unsigned char *)&chal, len);
            } else
                SEND3("TT %.*s", (int)blen, data);
            safe_free(data);

        } else if (strncmp(buf, "KK ", 3) == 0) {
            if (!packet) {
                SEND("BH received KK with no data! user=");
            } else if (ntlm_validate_packet(packet, NTLM_AUTHENTICATE) == NTLM_ERR_NONE) {
                if (ntlm_unpack_auth((ntlm_authenticate *)packet, user, domain, decodedLen) == NTLM_ERR_NONE) {
                    lc(user);
                    if (strip_domain_enabled) {
                        SEND2("AF %s", user);
                    } else {
                        SEND4("AF %s%s%s", domain, (*domain?"\\":""), user);
                    }
                } else {
                    lc(user);
                    SEND4("NA invalid credentials, user=%s%s%s", domain, (*domain?"\\":""), user);
                }
            } else {
                SEND("BH wrong packet type! user=");
            }
        }
    }
    exit(0);
}