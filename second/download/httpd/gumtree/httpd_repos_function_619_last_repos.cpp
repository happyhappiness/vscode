static int echo_header(void *v, const char *key, const char *val)
{
    edit_do *ed = v;

    /* If the input header (key) matches the regex, echo it intact to
     * r->headers_out.
     */
    if (!ap_regexec(ed->hdr->regex, key, 0, NULL, 0)) {
        apr_table_add(ed->r->headers_out, key, val);
    }

    return 1;
}