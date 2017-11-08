static int hb_table_check(void *rec, const char *key, const char *value)
{
    hb_table_baton_t *b = (hb_table_baton_t*)rec;
    if (strcmp(key, "path") != 0) {
        b->msg = apr_psprintf(b->p,
                              "SerfCluster Heartbeat Invalid parameter '%s'",
                              key);
        return 1;
    }

    return 0;
}