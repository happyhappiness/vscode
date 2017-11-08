const char *cache_table_getm(apr_pool_t *p, const apr_table_t *t,
        const char *key)
{
    cache_table_getm_t state;

    state.p = p;
    state.first = NULL;
    state.merged = NULL;

    apr_table_do(cache_table_getm_do, &state, t, key, NULL);

    if (!state.first) {
        return NULL;
    }
    else if (!state.merged) {
        return state.first;
    }
    else {
        return apr_array_pstrcat(p, state.merged, ',');
    }
}