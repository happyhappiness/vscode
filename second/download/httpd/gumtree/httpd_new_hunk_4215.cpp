        next->next = res;
    }

    *new = res;
    *item_size = desc.size;
    *item_num = desc.num;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                 APLOGNO(02303)
                 "attach found %s: %"APR_SIZE_T_FMT"/%u", fname,
                 *item_size, *item_num);
    return APR_SUCCESS;
}

static apr_status_t slotmem_dptr(ap_slotmem_instance_t *slot,
                                 unsigned int id, void **mem)
{
