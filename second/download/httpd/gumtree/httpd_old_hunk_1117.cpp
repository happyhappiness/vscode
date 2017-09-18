    ap_max_mem_free = (apr_uint32_t)value * 1024;

    return NULL;
}

#endif /* AP_MPM_WANT_SET_MAX_MEM_FREE */
