static int add_auth_info(request_rec *r)
{
    const digest_config_rec *conf =
                (digest_config_rec *) ap_get_module_config(r->per_dir_config,
                                                           &auth_digest_module);
    digest_header_rec *resp =
                (digest_header_rec *) ap_get_module_config(r->request_config,
                                                           &auth_digest_module);
    const char *ai = NULL, *digest = NULL, *nextnonce = "";

    if (resp == NULL || !resp->needed_auth || conf == NULL) {
        return OK;
    }


    /* rfc-2069 digest
     */
    if (resp->message_qop == NULL) {
        /* old client, so calc rfc-2069 digest */

#ifdef SEND_DIGEST
        /* most of this totally bogus because the handlers don't set the
         * headers until the final handler phase (I wonder why this phase
         * is called fixup when there's almost nothing you can fix up...)
         *
         * Because it's basically impossible to get this right (e.g. the
         * Content-length is never set yet when we get here, and we can't
         * calc the entity hash) it's best to just leave this #def'd out.
         */
        char date[APR_RFC822_DATE_LEN];
        apr_rfc822_date(date, r->request_time);
        char *entity_info =
            ap_md5(r->pool,
                   (unsigned char *) apr_pstrcat(r->pool, resp->raw_request_uri,
                       ":",
                       r->content_type ? r->content_type : ap_default_type(r), ":",
                       hdr(r->headers_out, "Content-Length"), ":",
                       r->content_encoding ? r->content_encoding : "", ":",
                       hdr(r->headers_out, "Last-Modified"), ":",
                       r->no_cache && !apr_table_get(r->headers_out, "Expires") ?
                            date :
                            hdr(r->headers_out, "Expires"),
                       NULL));
        digest =
            ap_md5(r->pool,
                   (unsigned char *)apr_pstrcat(r->pool, conf->ha1, ":",
                                               resp->nonce, ":",
                                               r->method, ":",
                                               date, ":",
                                               entity_info, ":",
                                               ap_md5(r->pool, (unsigned char *) ""), /* H(entity) - TBD */
                                               NULL));
#endif
    }


    /* setup nextnonce
     */
    if (conf->nonce_lifetime > 0) {
        /* send nextnonce if current nonce will expire in less than 30 secs */
        if ((r->request_time - resp->nonce_time) > (conf->nonce_lifetime-NEXTNONCE_DELTA)) {
            nextnonce = apr_pstrcat(r->pool, ", nextnonce=\"",
                                   gen_nonce(r->pool, r->request_time,
                                             resp->opaque, r->server, conf),
                                   "\"", NULL);
            if (resp->client)
                resp->client->nonce_count = 0;
        }
    }
    else if (conf->nonce_lifetime == 0 && resp->client) {
        const char *nonce = gen_nonce(r->pool, 0, resp->opaque, r->server,
                                      conf);
        nextnonce = apr_pstrcat(r->pool, ", nextnonce=\"", nonce, "\"", NULL);
        memcpy(resp->client->last_nonce, nonce, NONCE_LEN+1);
    }
    /* else nonce never expires, hence no nextnonce */


    /* do rfc-2069 digest
     */
    if (conf->qop_list[0] && !strcasecmp(conf->qop_list[0], "none")
        && resp->message_qop == NULL) {
        /* use only RFC-2069 format */
        if (digest) {
            ai = apr_pstrcat(r->pool, "digest=\"", digest, "\"", nextnonce,NULL);
        }
        else {
            ai = nextnonce;
        }
    }
    else {
        const char *resp_dig, *ha1, *a2, *ha2;

        /* calculate rspauth attribute
         */
        if (resp->algorithm && !strcasecmp(resp->algorithm, "MD5-sess")) {
            ha1 = get_session_HA1(r, resp, conf, 0);
            if (!ha1) {
                ap_log_rer