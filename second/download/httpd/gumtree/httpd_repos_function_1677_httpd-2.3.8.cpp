static int static_table_check(void *rec, const char *key, const char *value)
{
    hb_table_baton_t *b = (hb_table_baton_t*)rec;
    if (strcmp(key, "hosts") != 0 &&
        strcmp(key, "order") != 0) {
        b->msg = apr_psprintf(b->p,
                              "SerfCluster Static Invalid parameter '%s'",
                              key);
        return 1;
    }
    
    return 0;
}