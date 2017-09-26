    t->index_initialized |= s->index_initialized;
}

APR_DECLARE(void) apr_table_overlap(apr_table_t *a, const apr_table_t *b,
				    unsigned flags)
{
    const int m = a->a.nelts;
    const int n = b->a.nelts;
    apr_pool_t *p = b->a.pool;

    if (m + n == 0) {
        return;
    }

    /* copy (extend) a using b's pool */
    if (a->a.pool != p) {
        make_array_core(&a->a, p, m+n, sizeof(apr_table_entry_t), 0);
    }

    apr_table_cat(a, b);

    apr_table_compress(a, flags);
}
