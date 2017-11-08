static apr_status_t shm_cleanup_owner(void *m_)
{
    apr_shm_t *m = (apr_shm_t *)m_;

    /* anonymous shared memory */
    if (m->filename == NULL) {
#if APR_USE_SHMEM_MMAP_ZERO || APR_USE_SHMEM_MMAP_ANON
        if (munmap(m->base, m->realsize) == -1) {
            return errno;
        }
        return APR_SUCCESS;
#elif APR_USE_SHMEM_SHMGET_ANON
        if (shmdt(m->base) == -1) {
            return errno;
        }
        /* This segment will automatically remove itself after all
         * references have detached. */
        return APR_SUCCESS;
#endif
    }

    /* name-based shared memory */
    else {
#if APR_USE_SHMEM_MMAP_TMP
        if (munmap(m->base, m->realsize) == -1) {
            return errno;
        }
        if (access(m->filename, F_OK)) {
            return APR_SUCCESS;
        }
        else {
            return apr_file_remove(m->filename, m->pool);
        }
#elif APR_USE_SHMEM_MMAP_SHM
        if (munmap(m->base, m->realsize) == -1) {
            return errno;
        }
        if (shm_unlink(m->filename) == -1) {
            return errno;
        }
        return APR_SUCCESS;
#elif APR_USE_SHMEM_SHMGET
        /* Indicate that the segment is to be destroyed as soon
         * as all processes have detached. This also disallows any
         * new attachments to the segment. */
        if (shmctl(m->shmid, IPC_RMID, NULL) == -1 && errno != EINVAL) {
            return errno;
        }
        if (shmdt(m->base) == -1) {
            return errno;
        }
        if (access(m->filename, F_OK)) {
            return APR_SUCCESS;
        }
        else {
            return apr_file_remove(m->filename, m->pool);
        }
#else
        return APR_ENOTIMPL;
#endif
    }
}