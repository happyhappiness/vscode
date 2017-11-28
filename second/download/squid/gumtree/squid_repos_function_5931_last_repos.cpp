const char *
make_challenge(char *domain, char *domain_controller)
{
    /* trying to circumvent some strange problem wih pointers in SMBLib */
    /* Ugly as hell, but the lib is going to be dropped... */
    strncpy(my_domain, domain, sizeof(my_domain)-1);
    my_domain[sizeof(my_domain)-1] = '\0';
    strncpy(my_domain_controller, domain_controller, sizeof(my_domain_controller)-1);
    my_domain_controller[sizeof(my_domain_controller)-1] = '\0';

    if (init_challenge(my_domain, my_domain_controller) > 0) {
        return NULL;
    }

    ntlm_challenge chal;
    uint32_t flags = NTLM_REQUEST_NON_NT_SESSION_KEY |
                     NTLM_CHALLENGE_TARGET_IS_DOMAIN |
                     NTLM_NEGOTIATE_ALWAYS_SIGN |
                     NTLM_NEGOTIATE_USE_NTLM |
                     NTLM_NEGOTIATE_USE_LM |
                     NTLM_NEGOTIATE_ASCII;
    ntlm_make_challenge(&chal, my_domain, my_domain_controller, (char *)challenge, NTLM_NONCE_LEN, flags);

    size_t len = sizeof(chal) - sizeof(chal.payload) + le16toh(chal.target.maxlen);
    // for lack of a good NTLM token size limit, allow up to what the helper input can be
    // validations later will expect to be limited to that size.
    static uint8_t b64buf[HELPER_INPUT_BUFFER-10]; /* 10 for other line fields, delimiters and terminator */
    if (base64_encode_len(len) < sizeof(b64buf)-1) {
        debug("base64 encoding of the token challenge will exceed %" PRIuSIZE " bytes", sizeof(b64buf));
        return NULL;
    }

    struct base64_encode_ctx ctx;
    base64_encode_init(&ctx);
    size_t blen = base64_encode_update(&ctx, b64buf, len, reinterpret_cast<const uint8_t *>(&chal));
    blen += base64_encode_final(&ctx, b64buf+blen);
    b64buf[blen] = '\0';
    return reinterpret_cast<const char*>(b64buf);
}