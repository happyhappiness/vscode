static int have_ssl_compression(request_rec *r)
{
    const char *comp;
    if (mod_deflate_ssl_var == NULL)
        return 0;
    comp = mod_deflate_ssl_var(r->pool, r->server, r->connection, r,
                               "SSL_COMPRESS_METHOD");
    if (comp == NULL || *comp == '\0' || strcmp(comp, "NULL") == 0)
        return 0;
    return 1;
}