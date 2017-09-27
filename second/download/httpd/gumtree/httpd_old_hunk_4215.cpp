        next->next = res;
    }

    *new = res;
    *item_size = desc.size;
    *item_num = desc.num;
    return APR_SUCCESS;
}

static apr_status_t slotmem_dptr(ap_slotmem_instance_t *slot,
                                 unsigned int id, void **mem)
{
