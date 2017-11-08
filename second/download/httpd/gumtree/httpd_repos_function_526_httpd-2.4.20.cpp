static int magic_rsl_printf(request_rec *r, char *str,...)
{
    va_list ap;

    char buf[MAXMIMESTRING];

    /* assemble the string into the buffer */
    va_start(ap, str);
    apr_vsnprintf(buf, sizeof(buf), str, ap);
    va_end(ap);

    /* add the buffer to the list */
    return magic_rsl_add(r, apr_pstrdup(r->pool, buf));
}