static apr_status_t _file_dup(apr_file_t **new_file, 
                              apr_file_t *old_file, apr_pool_t *p,
                              int which_dup)
{
    int rv;
    
    if ((*new_file) == NULL) {
        if (which_dup == 1) {
            (*new_file) = (apr_file_t *)apr_pcalloc(p, sizeof(apr_file_t));
            if ((*new_file) == NULL) {
                return APR_ENOMEM;
            }
            (*new_file)->pool = p;
        } else {
            /* We can't dup2 unless we have a valid new_file */
            return APR_EINVAL;
        }
    }

    if (which_dup == 2) {
        rv = dup2(old_file->filedes, (*new_file)->filedes);
    } else {
        rv = ((*new_file)->filedes = dup(old_file->filedes)); 
    }

    if (rv == -1)
        return errno;
    
    (*new_file)->fname = apr_pstrdup(p, old_file->fname);
    (*new_file)->buffered = old_file->buffered;

    /* If the existing socket in a dup2 is already buffered, we
     * have an existing and valid (hopefully) mutex, so we don't
     * want to create it again as we could leak!
     */
#if APR_HAS_THREADS
    if ((*new_file)->buffered && !(*new_file)->thlock && old_file->thlock) {
        apr_thread_mutex_create(&((*new_file)->thlock),
                                APR_THREAD_MUTEX_DEFAULT, p);
    }
#endif
    /* As above, only create the buffer if we haven't already
     * got one.
     */
    if ((*new_file)->buffered && !(*new_file)->buffer) {
        (*new_file)->buffer = apr_palloc(p, APR_FILE_BUFSIZE);
    }

    /* this is the way dup() works */
    (*new_file)->blocking = old_file->blocking; 

    /* make sure unget behavior is consistent */
    (*new_file)->ungetchar = old_file->ungetchar;

    /* apr_file_dup() clears the inherit attribute, user must call 
     * apr_file_inherit_set() again on the dupped handle, as necessary.
     */
    (*new_file)->flags = old_file->flags & ~APR_INHERIT;

    return APR_SUCCESS;
}