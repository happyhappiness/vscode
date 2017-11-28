    if (s->dynamicCertMemCacheSize != std::numeric_limits<size_t>::max())
        storeAppendPrintf(e, "dynamic_cert_mem_cache_size=%lu%s\n", (unsigned long)s->dynamicCertMemCacheSize, B_BYTES_STR);
#endif
}

static void
dump_http_port_list(StoreEntry * e, const char *n, const http_port_list * s)
{
    while (s) {
        dump_generic_http_port(e, n, s);
        storeAppendPrintf(e, "\n");
        s = s->next;
    }
}

static void
free_http_port_list(http_port_list ** head)
{
    http_port_list *s;

    while ((s = *head) != NULL) {
        *head = s->next;
        cbdataReferenceDone(s);
    }
}

#if USE_SSL

// TODO: merge better with parse_http_port_list
static void
parse_https_port_list(https_port_list ** head)
{
    char *token;
    https_port_list *s;

    token = strtok(NULL, w_space);

    if (!token)
        self_destruct();

    s = new https_port_list;
    parse_http_port_specification(&s->http, token);

    /* parse options ... */
    while ((token = strtok(NULL, w_space))) {
        parse_http_port_option(s, token);
    }

    while (*head) {
        http_port_list ** headTmp = &(*head)->http.next;
        head = (https_port_list **)headTmp;
    }

    *head = s;
}

static void
dump_https_port_list(StoreEntry * e, const char *n, const https_port_list * s)
{
    dump_http_port_list(e, n, s);
}

static void
free_https_port_list(https_port_list ** head)
{
    free_http_port_list((http_port_list**)head);
}

#if 0
static int
check_null_https_port_list(const https_port_list * s)
{
    return NULL == s;
}

#endif

#endif /* USE_SSL */

void
configFreeMemory(void)
{
    free_all();
}

void
requirePathnameExists(const char *name, const char *path)
{

