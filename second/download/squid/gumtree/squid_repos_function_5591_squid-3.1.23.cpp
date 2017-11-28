const char *
ntlm_make_challenge(char *domain, char *domain_controller,
                    char *challenge_nonce, int challenge_nonce_len)
{
    ntlm_challenge ch;
    int pl = 0;
    const char *encoded;
    memset(&ch, 0, sizeof(ntlm_challenge));	/* reset */
    memcpy(ch.signature, "NTLMSSP", 8);		/* set the signature */
    ch.type = htole32(NTLM_CHALLENGE);	/* this is a challenge */
    ntlm_add_to_payload(ch.payload, &pl, &ch.target, domain, strlen(domain),
                        NTLM_CHALLENGE_HEADER_OFFSET);
    ch.flags = htole32(
                   REQUEST_NON_NT_SESSION_KEY |
                   CHALLENGE_TARGET_IS_DOMAIN |
                   NEGOTIATE_ALWAYS_SIGN |
                   NEGOTIATE_USE_NTLM |
                   NEGOTIATE_USE_LM |
                   NEGOTIATE_ASCII |
                   0
               );
    ch.context_low = 0;		/* check this out */
    ch.context_high = 0;
    memcpy(ch.challenge, challenge_nonce, challenge_nonce_len);
    encoded = base64_encode_bin((char *) &ch, NTLM_CHALLENGE_HEADER_OFFSET + pl);
    return encoded;
}