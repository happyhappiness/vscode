static void
dump_http_port_list(StoreEntry * e, const char *n, const http_port_list * s)
{
    while (s) {
        dump_generic_http_port(e, n, s);
        storeAppendPrintf(e, "\n");
        s = s->next;
    }
}