static apr_status_t mmap_cleanup(void *themmap)
{
    apr_mmap_t *mm = themmap;
    apr_status_t rv = 0;

    if (!mm->is_owner) {
        return APR_EINVAL;
    }
    else if (!mm->mhandle) {
        return APR_ENOENT;
    }

    if (mm->mv) {
        if (!UnmapViewOfFile(mm->mv))
        {
            apr_status_t rv = apr_get_os_error();
            CloseHandle(mm->mhandle);
            mm->mv = NULL;
            mm->mhandle = NULL;
            return rv;
        }
        mm->mv = NULL;
    }
    if (mm->mhandle) 
    {
        if (!CloseHandle(mm->mhandle))
        {
            apr_status_t rv = apr_get_os_error();
            CloseHandle(mm->mhandle);
            mm->mhandle = NULL;
            return rv;
        }
        mm->mhandle = NULL;
    }
    return APR_SUCCESS;
}