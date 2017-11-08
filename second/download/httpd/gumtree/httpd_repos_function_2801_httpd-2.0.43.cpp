static void make_array_core(apr_array_header_t *res, apr_pool_t *p,
			    int nelts, int elt_size, int clear)
{
    /*
     * Assure sanity if someone asks for
     * array of zero elts.
     */
    if (nelts < 1) {
        nelts = 1;
    }

    if (clear) {
        res->elts = apr_pcalloc(p, nelts * elt_size);
    }
    else {
        res->elts = apr_palloc(p, nelts * elt_size);
    }

    res->pool = p;
    res->elt_size = elt_size;
    res->nelts = 0;		/* No active elements yet... */
    res->nalloc = nelts;	/* ...but this many allocated */
}