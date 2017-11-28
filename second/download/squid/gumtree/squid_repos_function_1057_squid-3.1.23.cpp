static void
free_http_header_access(header_mangler header[])
{
    int i;

    for (i = 0; i < HDR_ENUM_END; i++) {
        free_acl_access(&header[i].access_list);
    }
}