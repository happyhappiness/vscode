static char* process_tags(header_entry *hdr, request_rec *r)
{
    int i;
    const char *s;
    char *str = NULL;

    format_tag *tag = (format_tag*) hdr->ta->elts;

    for (i = 0; i < hdr->ta->nelts; i++) {
        s = tag[i].func(r, tag[i].arg);
        if (str == NULL)
            str = apr_pstrdup(r->pool, s);
        else
            str = apr_pstrcat(r->pool, str, s, NULL);
    }
    return str ? str : "";
}