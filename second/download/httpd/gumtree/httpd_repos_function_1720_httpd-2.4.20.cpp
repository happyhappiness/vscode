static char *find_item_by_request(request_rec *r, apr_array_header_t *list, int path_only)
{
    return find_item(ap_field_noparam(r->pool, r->content_type),
                     r->content_encoding, r->filename, list, path_only);
}