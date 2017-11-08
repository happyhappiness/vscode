static void parse_negotiate_header(request_rec *r, negotiation_state *neg)
{
    const char *negotiate = apr_table_get(r->headers_in, "Negotiate");
    char *tok;

    /* First, default to no TCN, no Alternates, and the original Apache
     * negotiation algorithm with fiddles for broken browser configs.
     *
     * To save network bandwidth, we do not configure to send an
     * Alternates header to the user agent by default.  User
     * agents that want an Alternates header for agent-driven
     * negotiation will have to request it by sending an
     * appropriate Negotiate header.
     */
    neg->ua_supports_trans   = 0;
    neg->send_alternates     = 0;
    neg->may_choose          = 1;
    neg->use_rvsa            = 0;
    neg->dont_fiddle_headers = 0;

    if (!negotiate)
        return;

    if (strcmp(negotiate, "trans") == 0) {
        /* Lynx 2.7 and 2.8 send 'negotiate: trans' even though they
         * do not support transparent content negotiation, so for Lynx we
         * ignore the negotiate header when its contents are exactly "trans".
         * If future versions of Lynx ever need to say 'negotiate: trans',
         * they can send the equivalent 'negotiate: trans, trans' instead
         * to avoid triggering the workaround below.
         */
        const char *ua = apr_table_get(r->headers_in, "User-Agent");

        if (ua && (strncmp(ua, "Lynx", 4) == 0))
            return;
    }

    neg->may_choose = 0;  /* An empty Negotiate would require 300 response */

    while ((tok = ap_get_list_item(neg->pool, &negotiate)) != NULL) {

        if (strcmp(tok, "trans") == 0 ||
            strcmp(tok, "vlist") == 0 ||
            strcmp(tok, "guess-small") == 0 ||
            apr_isdigit(tok[0]) ||
            strcmp(tok, "*") == 0) {

            /* The user agent supports transparent negotiation */
            neg->ua_supports_trans = 1;

            /* Send-alternates could be configurable, but note
             * that it must be 1 if we have 'vlist' in the
             * negotiate header.
             */
            neg->send_alternates = 1;

            if (strcmp(tok, "1.0") == 0) {
                /* we may use the RVSA/1.0 algorithm, configure for it */
                neg->may_choose = 1;
                neg->use_rvsa = 1;
                neg->dont_fiddle_headers = 1;
            }
            else if (tok[0] == '*') {
                /* we may use any variant selection algorithm, configure
                 * to use the Apache algorithm
                 */
                neg->may_choose = 1;

                /* We disable header fiddles on the assumption that a
                 * client sending Negotiate knows how to send correct
                 * headers which don't need fiddling.
                 */
                neg->dont_fiddle_headers = 1;
            }
        }
    }

#ifdef NEG_DEBUG
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00680)
            "dont_fiddle_headers=%d use_rvsa=%d ua_supports_trans=%d "
            "send_alternates=%d, may_choose=%d",
            neg->dont_fiddle_headers, neg->use_rvsa,
            neg->ua_supports_trans, neg->send_alternates, neg->may_choose);
#endif

}