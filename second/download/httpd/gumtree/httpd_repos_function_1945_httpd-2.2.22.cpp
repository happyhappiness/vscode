static const char* authn_ldap_xlate_password(request_rec *r,
                                             const char* sent_password)
{
    apr_xlate_t *convset = NULL;
    apr_size_t inbytes;
    apr_size_t outbytes;
    char *outbuf;

    if (charset_conversions && (convset = get_conv_set(r)) ) {
        inbytes = strlen(sent_password);
        outbytes = (inbytes+1)*3;
        outbuf = apr_pcalloc(r->pool, outbytes);

        /* Convert the password to UTF-8. */
        if (apr_xlate_conv_buffer(convset, sent_password, &inbytes, outbuf,
                                  &outbytes) == APR_SUCCESS)
            return outbuf;
    }

    return sent_password;
}