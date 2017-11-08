static APR_INLINE char *find_multiple_headers(apr_pool_t *pool,
                                              const apr_table_t *table,
                                              const char *key)
{
    const apr_array_header_t *elts;
    const apr_table_entry_t *t_elt;
    const apr_table_entry_t *t_end;
    apr_size_t len;
    struct sle {
        struct sle *next;
        const char *value;
        apr_size_t len;
    } *result_list, *rp;

    elts = apr_table_elts(table);

    if (!elts->nelts) {
        return NULL;
    }

    t_elt = (const apr_table_entry_t *)elts->elts;
    t_end = t_elt + elts->nelts;
    len = 1; /* \0 */
    result_list = rp = NULL;

    do {
        if (!strcasecmp(t_elt->key, key)) {
            if (!result_list) {
                result_list = rp = apr_palloc(pool, sizeof(*rp));
            }
            else {
                rp = rp->next = apr_palloc(pool, sizeof(*rp));
                len += 2; /* ", " */
            }

            rp->next = NULL;
            rp->value = t_elt->val;
            rp->len = strlen(rp->value);

            len += rp->len;
        }
        ++t_elt;
    } while (t_elt < t_end);

    if (result_list) {
        char *result = apr_palloc(pool, len);
        char *cp = result;

        rp = result_list;
        while (rp) {
            if (rp != result_list) {
                *cp++ = ',';
                *cp++ = ' ';
            }
            memcpy(cp, rp->value, rp->len);
            cp += rp->len;
            rp = rp->next;
        }
        *cp = '\0';

        return result;
    }

    return NULL;
}