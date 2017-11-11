static APR_INLINE void vhost_alias_checkspace(request_rec *r, char *buf,
                                             char **pdest, int size)
{
    /* XXX: what if size > HUGE_STRING_LEN? */
    if (*pdest + size > buf + HUGE_STRING_LEN) {
        **pdest = '\0';
        if (r->filename) {
            r->filename = apr_pstrcat(r->pool, r->filename, buf, NULL);
        }
        else {
            r->filename = apr_pstrdup(r->pool, buf);
        }
        *pdest = buf;
    }
}