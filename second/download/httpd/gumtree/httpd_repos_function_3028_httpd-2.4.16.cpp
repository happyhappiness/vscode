static void fake_basic_authentication(request_rec *r, auth_form_config_rec *conf,
                                      const char *user, const char *pw)
{
    if (conf->fakebasicauth) {
        char *basic = apr_pstrcat(r->pool, user, ":", pw, NULL);
        apr_size_t size = (apr_size_t) strlen(basic);
        char *base64 = apr_palloc(r->pool,
                                  apr_base64_encode_len(size + 1) * sizeof(char));
        apr_base64_encode(base64, basic, size);
        apr_table_setn(r->headers_in, "Authorization",
                       apr_pstrcat(r->pool, "Basic ", base64, NULL));
    }
}