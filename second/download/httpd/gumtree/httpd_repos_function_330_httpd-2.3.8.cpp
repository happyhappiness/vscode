static const char *dav_xml_escape_uri(apr_pool_t *p, const char *uri)
{
    const char *e_uri = ap_escape_uri(p, uri);

    /* check the easy case... */
    if (ap_strchr_c(e_uri, '&') == NULL)
        return e_uri;

    /* there was a '&', so more work is needed... sigh. */

    /*
     * Note: this is a teeny bit of overkill since we know there are no
     * '<' or '>' characters, but who cares.
     */
    return apr_xml_quote_string(p, e_uri, 0);
}