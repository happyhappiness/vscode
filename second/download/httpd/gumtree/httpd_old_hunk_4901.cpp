    *inuse = 1;
    *id = i;
    (*slot->num_free)--;
    return APR_SUCCESS;
}

static apr_status_t slotmem_release(ap_slotmem_instance_t *slot,
                                    unsigned int id)
{
    char *inuse;

    if (!slot) {
