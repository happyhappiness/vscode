static void authn_ldap_build_filter(char *filtbuf,
                             request_rec *r,
                             const char* sent_user,
                             const char* sent_filter,
                             authn_ldap_config_t *sec)
{
    char *p, *q, *filtbuf_end;
    char *user, *filter;
    apr_xlate_t *convset = NULL;
    apr_size_t inbytes;
    apr_size_t outbytes;
    char *outbuf;

    if (sent_user != NULL) {
        user = apr_pstrdup (r->pool, sent_user);
    }
    else
        return;

    if (sent_filter != NULL) {
        filter = apr_pstrdup (r->pool, sent_filter);
    }
    else
        filter = sec->filter;

    if (charset_conversions) {
        convset = get_conv_set(r);
    }

    if (convset) {
        inbytes = strlen(user);
        outbytes = (inbytes+1)*3;
        outbuf = apr_pcalloc(r->pool, outbytes);

        /* Convert the user name to UTF-8.  This is only valid for LDAP v3 */
        if (apr_xlate_conv_buffer(convset, user, &inbytes, outbuf, &outbytes) == APR_SUCCESS) {
            user = apr_pstrdup(r->pool, outbuf);
        }
    }

    /*
     * Create the first part of the filter, which consists of the
     * config-supplied portions.
     */
    apr_snprintf(filtbuf, FILTER_LENGTH, "(&(%s)(%s=", filter, sec->attribute);

    /*
     * Now add the client-supplied username to the filter, ensuring that any
     * LDAP filter metachars are escaped.
     */
    filtbuf_end = filtbuf + FILTER_LENGTH - 1;
#if APR_HAS_MICROSOFT_LDAPSDK
    for (p = user, q=filtbuf + strlen(filtbuf);
         *p && q < filtbuf_end; ) {
        if (strchr("*()\\", *p) != NULL) {
            if ( q + 3 >= filtbuf_end)
              break;  /* Don't write part of escape sequence if we can't write all of it */
            *q++ = '\\';
            switch ( *p++ )
            {
              case '*':
                *q++ = '2';
                *q++ = 'a';
                break;
              case '(':
                *q++ = '2';
                *q++ = '8';
                break;
              case ')':
                *q++ = '2';
                *q++ = '9';
                break;
              case '\\':
                *q++ = '5';
                *q++ = 'c';
                break;
                        }
        }
        else
            *q++ = *p++;
    }
#else
    for (p = user, q=filtbuf + strlen(filtbuf);
         *p && q < filtbuf_end; *q++ = *p++) {
        if (strchr("*()\\", *p) != NULL) {
            *q++ = '\\';
            if (q >= filtbuf_end) {
              break;
            }
        }
    }
#endif
    *q = '\0';

    /*
     * Append the closing parens of the filter, unless doing so would
     * overrun the buffer.
     */
    if (q + 2 <= filtbuf_end)
        strcat(filtbuf, "))");
}