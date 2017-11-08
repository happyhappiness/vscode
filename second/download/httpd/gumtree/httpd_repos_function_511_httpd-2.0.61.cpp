static int echo_header(echo_do *v, const char *key, const char *val)
{
    /* If the input header (key) matches the regex, echo it intact to 
     * r->headers_out.
     */
    if (!ap_regexec(v->hdr->regex, key, 0, NULL, 0)) {
        apr_table_add(v->r->headers_out, key, val);
    }

    return 1;
}