static apr_status_t shm_cleanup_attach(void *m_)
{
    apr_shm_t *m = (apr_shm_t *)m_;

    if (m->filename == NULL) {
        /* It doesn't make sense to detach from an anonymous memory segment. */
        return APR_EINVAL;
    }
    else {
#if APR_USE_SHMEM_MMAP_TMP || APR_USE_SHMEM_MMAP_SHM
        if (munmap(m->base, m->realsize) == -1) {
            return errno;
        }
        return APR_SUCCESS;
#endif /* APR_USE_SHMEM_MMAP_TMP || APR_USE_SHMEM_MMAP_SHM */
#if APR_USE_SHMEM_SHMGET
        if (shmdt(m->base) == -1) {
            return errno;
        }
        return APR_SUCCESS;
#endif
    }

    return APR_ENOTIMPL;
}