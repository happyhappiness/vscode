static int compare_ipports(void *rec, const char *key, const char *value)
{
    conn_rec *c = (conn_rec*)rec;

    if (value && ((strcmp(value, "0.0.0.0") == 0) ||
                  (strcmp(value, c->local_ip) == 0))) {
        return 0;
    }
    return 1;
}