static int isSecureConnEx (const server_rec *s, const conn_rec *c, const apr_table_t *t)
{
    char port[8];

    itoa((c->local_addr)->port, port, 10);
    if (!apr_table_do(compare_ipports, (void*)c, t, port, NULL))
    {
        return 1;
    }

    return 0;
}