static apr_status_t impl_pollcb_remove(apr_pollcb_t *pollcb,
                                       apr_pollfd_t *descriptor)
{
    apr_uint32_t i;

    for (i = 0; i < pollcb->nelts; i++) {
        if (descriptor->desc.s == pollcb->copyset[i]->desc.s) {
            /* Found an instance of the fd: remove this and any other copies */
            apr_uint32_t dst = i;
            apr_uint32_t old_nelts = pollcb->nelts;
            pollcb->nelts--;
            for (i++; i < old_nelts; i++) {
                if (descriptor->desc.s == pollcb->copyset[i]->desc.s) {
                    pollcb->nelts--;
                }
                else {
                    pollcb->pollset.ps[dst] = pollcb->pollset.ps[i];
                    pollcb->copyset[dst] = pollcb->copyset[i];
                    dst++;
                }
            }
            return APR_SUCCESS;
        }
    }

    return APR_NOTFOUND;
}