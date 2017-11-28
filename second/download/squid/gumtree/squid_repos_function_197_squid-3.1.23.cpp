void
send_bh_or_ld(char const *bhmessage, ntlm_authenticate * failedauth, int authlen)
{
#ifdef NTLM_FAIL_OPEN
    char *creds = NULL;
    if (last_ditch_enabled) {
        creds = fetch_credentials(failedauth, authlen);
        if (creds) {
            lc(creds);
            SEND2("LD %s", creds);
        } else {
            SEND("NA last-ditch on, but no credentials");
        }
    } else {
#endif
        SEND2("BH %s", bhmessage);
#ifdef NTLM_FAIL_OPEN
    }
#endif
}