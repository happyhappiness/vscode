void mod_auth_ldap_build_filter(char *filtbuf, 
                                request_rec *r, 
                                mod_auth_ldap_config_t *sec)
{
    char *p, *q, *filtbuf_end;
    /* 
     * Create the first part of the filter, which consists of the 
     * config-supplied portions.
     */
    apr_snprintf(filtbuf, FILTER_LENGTH, "(&(%s)(%s=", sec->filter, sec->attribute);

    /* 
     * Now add the client-supplied username to the filter, ensuring that any
     * LDAP filter metachars are escaped.
     */
    filtbuf_end = filtbuf + FILTER_LENGTH - 1;
    for (p = r->user, q=filtbuf + strlen(filtbuf);
         *p && q < filtbuf_end; *q++ = *p++) {
        if (strchr("*()\\", *p) != NULL) {
            *q++ = '\\';
            if (q >= filtbuf_end) {
	        break;
	    }
        }
    }
    *q = '\0';

    /* 
     * Append the closing parens of the filter, unless doing so would 
     * overrun the buffer.
     */
    if (q + 2 <= filtbuf_end)
        strcat(filtbuf, "))");
}