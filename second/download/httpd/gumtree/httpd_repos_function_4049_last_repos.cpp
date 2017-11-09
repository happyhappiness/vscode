static int send_header(void *data, const char *key, const char *val)
{
    char *header_line = NULL;
    hdr_ptr *hdr = (hdr_ptr*)data;

    header_line = apr_pstrcat(hdr->bb->p, key, ": ", val, CRLF, NULL);
    ap_xlate_proto_to_ascii(header_line, strlen(header_line));
    ap_fputs(hdr->f, hdr->bb, header_line);
    return 1;
}