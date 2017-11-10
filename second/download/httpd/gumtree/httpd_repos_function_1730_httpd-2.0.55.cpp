static const char *new_digest(const request_rec *r,
                              digest_header_rec *resp,
                              const digest_config_rec *conf)
{
    const char *ha1, *ha2, *a2;

    if (resp->algorithm && !strcasecmp(resp->algorithm, "MD5-sess")) {
        ha1 = get_session_HA1(r, resp, conf, 1);
        if (!ha1) {
            return NULL;
        }
    }
    else {
        ha1 = conf->ha1;
    }

    if (resp->message_qop && !strcasecmp(resp->message_qop, "auth-int")) {
        a2 = apr_pstrcat(r->pool, resp->method, ":", resp->uri, ":",
                         ap_md5(r->pool, (const unsigned char*) ""), NULL);
                         /* TBD */
    }
    else {
        a2 = apr_pstrcat(r->pool, resp->method, ":", resp->uri, NULL);
    }
    ha2 = ap_md5(r->pool, (const unsigned char *)a2);

    return ap_md5(r->pool,
                  (unsigned char *)apr_pstrcat(r->pool, ha1, ":", resp->nonce,
                                               ":", resp->nonce_count, ":",
                                               resp->cnonce, ":",
                                               resp->message_qop, ":", ha2,
                                               NULL));
}