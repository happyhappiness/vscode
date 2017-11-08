static APR_INLINE void copy_array_hdr_core(apr_array_header_t *res,
					   const apr_array_header_t *arr)
{
    res->elts = arr->elts;
    res->elt_size = arr->elt_size;
    res->nelts = arr->nelts;
    res->nalloc = arr->nelts;	/* Force overflow on push */
}