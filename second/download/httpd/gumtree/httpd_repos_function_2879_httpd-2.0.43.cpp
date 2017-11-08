static apr_status_t mmap_cleanup(void *themmap)
{
    apr_mmap_t *mm = themmap;
    int rv;

    if (!mm->is_owner) {
        return APR_EINVAL;
    }
    else if (mm->mm == (void *)-1) {
        return APR_ENOENT;
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