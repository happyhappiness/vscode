static int cache_table_getm_do(void *v, const char *key, const char *val)
{
    cache_table_getm_t *state = (cache_table_getm_t *) v;

    if (!state->first) {
        /**
         * The most common case is a single header, and this is covered by
         * a fast path that doesn't allocate any memory. On the second and
         * subsequent header, an array is created and the array concatenated
         * together to form the final value.
         */
        state->first = val;
    }
    else {
        const char **elt;
        if (!state->merged) {
            state->merged = apr_array_make(state->p, 10, sizeof(const char *));
            elt = apr_array_push(state->merged);
            *elt = state->first;
        }
        elt = apr_array_push(state->merged);
        *elt = val;
    }
    return 1;
}