static const char *dav_xml_escape_uri(apr_pool_t *p, const char *uri)
{
    /* check the easy case... */
    if (ap_strchr_c(uri, '&') == NULL)
        return uri;

    /* there was a '&', so more work is needed... sigh. */

    /*
     * Note: this is a teeny bit of overkill since we know there are no
     * '<' or '>' characters, but who cares.
     */
    return apr_xml_quote_string(p, uri, 0);
}