static apr_status_t mmap_cleanup(void *themmap)
{
    apr_mmap_t *mm = themmap;
    apr_mmap_t *next = APR_RING_NEXT(mm,link);
    int rv = 0;

    /* we no longer refer to the mmaped region */
    APR_RING_REMOVE(mm,link);
    APR_RING_NEXT(mm,link) = NULL;
    APR_RING_PREV(mm,link) = NULL;

    if (next != mm) {
        /* more references exist, so we're done */
        return APR_SUCCESS;
    }

#ifdef BEOS
    rv = delete_area(mm->area);
#else
    rv = munmap(mm->mm, mm->size);
#endif
    mm->mm = (void *)-1;

    if (rv == 0) {
        return APR_SUCCESS;
    }
    return errno;
}