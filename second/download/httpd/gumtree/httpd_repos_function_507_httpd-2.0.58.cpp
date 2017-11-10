static char *parse_format_string(apr_pool_t *p, header_entry *hdr, const char *s)
{
    char *res;

    /* No string to parse with unset and copy commands */
    if (hdr->action == hdr_unset ||
        hdr->action == hdr_echo) {
        return NULL;
    }

    hdr->ta = apr_array_make(p, 10, sizeof(format_tag));

    while (*s) {
        if ((res = parse_format_tag(p, (format_tag *) apr_array_push(hdr->ta), &s))) {
            return res;
        }
    }
    return NULL;
}