const char *
ntlm_make_negotiate(void)
{
    ntlm_negotiate ne;
    const char *encoded;
    memset(&ne, 0, sizeof(ntlm_negotiate));	/* reset */
    memcpy(ne.signature, "NTLMSSP", 8);		/* set the signature */
    ne.type = le32toh(NTLM_NEGOTIATE);	/* this is a challenge */
    ne.flags = le32toh(
                   NEGOTIATE_ALWAYS_SIGN |
                   NEGOTIATE_USE_NTLM |
                   NEGOTIATE_USE_LM |
                   NEGOTIATE_ASCII |
                   0
               );
    encoded = base64_encode_bin((char *) &ne, NEGOTIATE_LENGTH);
    debug("Negotiate packet not supplied - self generated\n");
    return encoded;
}