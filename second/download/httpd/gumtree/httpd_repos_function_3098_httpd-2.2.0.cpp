static apr_status_t _thread_rw_cleanup(void * data)
{
    apr_thread_rwlock_t *mutex = (apr_thread_rwlock_t*)data;

    if (mutex->ReadCount != 0) {
    	while (atomic_add(&mutex->ReadCount , -1) > 1){
            release_sem (mutex->Read);
    	}
    }
    if (mutex->WriteCount != 0) {
    	while (atomic_add(&mutex->WriteCount , -1) > 1){
            release_sem (mutex->Write);
    	}
    }
    if (mutex->LockCount != 0) {
    	while (atomic_add(&mutex->LockCount , -1) > 1){
            release_sem (mutex->Lock);
    	}
    }
    
    delete_sem(mutex->Read);
    delete_sem(mutex->Write);
    delete_sem(mutex->Lock);
    return APR_SUCCESS;
}