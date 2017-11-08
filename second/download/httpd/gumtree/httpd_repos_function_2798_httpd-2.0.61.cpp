static apr_status_t other_child_cleanup(void *data)
{
    apr_other_child_rec_t **pocr, *nocr;

    for (pocr = &other_children; *pocr; pocr = &(*pocr)->next) {
        if ((*pocr)->data == data) {
            nocr = (*pocr)->next;
            (*(*pocr)->maintenance) (APR_OC_REASON_UNREGISTER, (*pocr)->data, -1);
            *pocr = nocr;
            /* XXX: um, well we've just wasted some space in pconf ? */
            return APR_SUCCESS;
        }
    }
    return APR_SUCCESS;
}