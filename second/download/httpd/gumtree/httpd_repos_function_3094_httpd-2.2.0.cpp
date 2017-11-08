static apr_status_t _proc_mutex_cleanup(void * data)
{
    apr_proc_mutex_t *lock = (apr_proc_mutex_t*)data;
    if (lock->LockCount != 0) {
        /* we're still locked... */
    	while (atomic_add(&lock->LockCount , -1) > 1){
    	    /* OK we had more than one person waiting on the lock so 
    	     * the sem is also locked. Release it until we have no more
    	     * locks left.
    	     */
            release_sem (lock->Lock);
    	}
    }
    delete_sem(lock->Lock);
    return APR_SUCCESS;
}