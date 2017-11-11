static void free_dh_params(void)
{
    unsigned n;

    /* DH_free() is a noop for a NULL parameter, so these are harmless
     * in the (unexpected) case where these variables are already
     * NULL. */
    for (n = 0; n < sizeof(dhparams)/sizeof(dhparams[0]); n++) {
        DH_free(dhparams[n].dh);
        dhparams[n].dh = NULL;
    }
}