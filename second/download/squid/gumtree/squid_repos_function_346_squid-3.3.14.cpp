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
    int len = sizeof(chal) - sizeof(chal.payload) + le16toh(chal.target.maxlen);
    return base64_encode_bin((char *)&chal, len);
}