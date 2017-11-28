static void
free_http_header_replace(header_mangler header[])
{
    int i;

    for (i = 0; i < HDR_ENUM_END; i++) {
        if (header[i].replacement != NULL)
            safe_free(header[i].replacement);
    }
}