const char *
obtain_challenge(ntlm_negotiate * nego, int nego_length)
{
    const char *ch = NULL;

    debug("attempting SSPI challenge retrieval\n");
    ch = SSP_MakeChallenge(nego, nego_length);
    if (ch) {
        debug("Got it\n");
        return ch;		/* All went OK, returning */
    }
    return NULL;
}