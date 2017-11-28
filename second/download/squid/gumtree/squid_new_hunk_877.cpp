    mem_obj->object_sz = mem_obj->endOffset();

    store_status = STORE_OK;

    assert(mem_status == NOT_IN_MEMORY);

    if (!EBIT_TEST(flags, ENTRY_BAD_LENGTH) && !validLength())
        lengthWentBad("!validLength() in complete()");

#if USE_CACHE_DIGESTS
    if (mem_obj->request)
        mem_obj->request->hier.store_complete_stop = current_time;

#endif
