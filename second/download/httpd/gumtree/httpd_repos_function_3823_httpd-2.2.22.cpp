static apr_status_t impl_pollset_remove(apr_pollset_t *pollset,
                                        const apr_pollfd_t *descriptor)
{
    apr_uint32_t i;

    for (i = 0; i < pollset->nelts; i++) {
        if (descriptor->desc.s == pollset->p->query_set[i].desc.s) {
            /* Found an instance of the fd: remove this and any other copies */
            apr_uint32_t dst = i;
            apr_uint32_t old_nelts = pollset->nelts;
            pollset->nelts--;
            for (i++; i < old_nelts; i++) {
                if (descriptor->desc.s == pollset->p->query_set[i].desc.s) {
                    pollset->nelts--;
                }
                else {
                    pollset->p->pollset[dst] = pollset->p->pollset[i];
                    pollset->p->query_set[dst] = pollset->p->query_set[i];
                    dst++;
                }
            }
            return APR_SUCCESS;
        }
    }

    return APR_NOTFOUND;
}