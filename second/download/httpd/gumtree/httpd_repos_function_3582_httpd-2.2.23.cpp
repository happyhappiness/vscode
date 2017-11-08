static apr_status_t proc_mutex_fcntl_tryacquire(apr_proc_mutex_t *mutex)
{
    int rc;

    do {
        rc = fcntl(mutex->interproc->filedes, F_SETLK, &proc_mutex_lock_it);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
#if FCNTL_TRYACQUIRE_EACCES
        if (errno == EACCES) {
#else
        if (errno == EAGAIN) {
#endif
            return APR_EBUSY;
        }
        return errno;
    }
    mutex->curr_locked = 1;
    return APR_SUCCESS;
}

static apr_status_t proc_mutex_fcntl_release(apr_proc_mutex_t *mutex)
{
    int rc;

    mutex->curr_locked=0;
    do {
        rc = fcntl(mutex->interproc->filedes, F_SETLKW, &proc_mutex_unlock_it);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        return errno;
    }
    return APR_SUCCESS;
}

static const apr_proc_mutex_unix_lock_methods_t mutex_fcntl_methods =
{
#if APR_PROCESS_LOCK_IS_GLOBAL || !APR_HAS_THREADS || defined(FCNTL_IS_GLOBAL)
    APR_PROCESS_LOCK_MECH_IS_GLOBAL,
#else
    0,
#endif
    proc_mutex_fcntl_create,
    proc_mutex_fcntl_acquire,
    proc_mutex_fcntl_tryacquire,
    proc_mutex_fcntl_release,
    proc_mutex_fcntl_cleanup,
    proc_mutex_no_child_init,
    "fcntl"
};

#endif /* fcntl implementation */

#if APR_HAS_FLOCK_SERIALIZE

static apr_status_t proc_mutex_flock_release(apr_proc_mutex_t *);

static apr_status_t proc_mutex_flock_cleanup(void *mutex_)
{
    apr_status_t status;
    apr_proc_mutex_t *mutex=mutex_;

    if (mutex->curr_locked == 1) {
        status = proc_mutex_flock_release(mutex);
        if (status != APR_SUCCESS)
            return status;
    }
    if (mutex->interproc) { /* if it was opened properly */
        apr_file_close(mutex->interproc);
    }
    unlink(mutex->fname);
    return APR_SUCCESS;
}    

static apr_status_t proc_mutex_flock_create(apr_proc_mutex_t *new_mutex,
                                            const char *fname)
{
    int rv;
 
    if (fname) {
        new_mutex->fname = apr_pstrdup(new_mutex->pool, fname);
        rv = apr_file_open(&new_mutex->interproc, new_mutex->fname,
                           APR_FOPEN_CREATE | APR_FOPEN_WRITE | APR_FOPEN_EXCL,
                           APR_UREAD | APR_UWRITE,
                           new_mutex->pool);
    }
    else {
        new_mutex->fname = apr_pstrdup(new_mutex->pool, "/tmp/aprXXXXXX");
        rv = apr_file_mktemp(&new_mutex->interproc, new_mutex->fname,
                             APR_FOPEN_CREATE | APR_FOPEN_WRITE | APR_FOPEN_EXCL,
                             new_mutex->pool);
    }
 
    if (rv != APR_SUCCESS) {
        proc_mutex_flock_cleanup(new_mutex);
        return errno;
    }
    new_mutex->curr_locked = 0;
    apr_pool_cleanup_register(new_mutex->pool, (void *)new_mutex,
                              apr_proc_mutex_cleanup,
                              apr_pool_cleanup_null);
    return APR_SUCCESS;
}

static apr_status_t proc_mutex_flock_acquire(apr_proc_mutex_t *mutex)
{
    int rc;

    do {
        rc = flock(mutex->interproc->filedes, LOCK_EX);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        return errno;
    }
    mutex->curr_locked = 1;
    return APR_SUCCESS;
}

static apr_status_t proc_mutex_flock_tryacquire(apr_proc_mutex_t *mutex)
{
    int rc;

    do {
        rc = flock(mutex->interproc->filedes, LOCK_EX | LOCK_NB);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            return APR_EBUSY;
        }
        return errno;
    }
    mutex->curr_locked = 1;
    return APR_SUCCESS;
}

static apr_status_t proc_mutex_flock_release(apr_proc_mutex_t *mutex)
{
    int rc;

    mutex->curr_locked = 0;
    do {
        rc = flock(mutex->interproc->filedes, LOCK_UN);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        return errno;
    }
    return APR_SUCCESS;
}

static apr_status_t proc_mutex_flock_child_init(apr_proc_mutex_t **mutex,
                                                apr_pool_t *pool, 
                                                const char *fname)
{
    apr_proc_mutex_t *new_mutex;
    int rv;

    new_mutex = (apr_proc_mutex_t *)apr_palloc(pool, sizeof(apr_proc_mutex_t));

    memcpy(new_mutex, *mutex, sizeof *new_mutex);
    new_mutex->pool = pool;
    if (!fname) {
        fname = (*mutex)->fname;
    }
    new_mutex->fname = apr_pstrdup(pool, fname);
    rv = apr_file_open(&new_mutex->interproc, new_mutex->fname,
                       APR_FOPEN_WRITE, 0, new_mutex->pool);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    *mutex = new_mutex;
    return APR_SUCCESS;
}

static const apr_proc_mutex_unix_lock_methods_t mutex_flock_methods =
{
#if APR_PROCESS_LOCK_IS_GLOBAL || !APR_HAS_THREADS || defined(FLOCK_IS_GLOBAL)
    APR_PROCESS_LOCK_MECH_IS_GLOBAL,
#else
    0,
#endif
    proc_mutex_flock_create,
    proc_mutex_flock_acquire,
    proc_mutex_flock_tryacquire,
    proc_mutex_flock_release,
    proc_mutex_flock_cleanup,
    proc_mutex_flock_child_init,
    "flock"
};

#endif /* flock implementation */

void apr_proc_mutex_unix_setup_lock(void)
{
    /* setup only needed for sysvsem and fnctl */
#if APR_HAS_SYSVSEM_SERIALIZE
    proc_mutex_sysv_setup();
#endif
#if APR_HAS_FCNTL_SERIALIZE
    proc_mutex_fcntl_setup();
#endif
}

static apr_status_t proc_mutex_choose_method(apr_proc_mutex_t *new_mutex, apr_lockmech_e mech)
{
    switch (mech) {
    case APR_LOCK_FCNTL:
#if APR_HAS_FCNTL_SERIALIZE
        new_mutex->inter_meth = &mutex_fcntl_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_LOCK_FLOCK:
#if APR_HAS_FLOCK_SERIALIZE
        new_mutex->inter_meth = &mutex_flock_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_LOCK_SYSVSEM:
#if APR_HAS_SYSVSEM_SERIALIZE
        new_mutex->inter_meth = &mutex_sysv_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_LOCK_POSIXSEM:
#if APR_HAS_POSIXSEM_SERIALIZE
        new_mutex->inter_meth = &mutex_posixsem_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_LOCK_PROC_PTHREAD:
#if APR_HAS_PROC_PTHREAD_SERIALIZE
        new_mutex->inter_meth = &mutex_proc_pthread_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_LOCK_DEFAULT:
#if APR_USE_FLOCK_SERIALIZE
        new_mutex->inter_meth = &mutex_flock_methods;
#elif APR_USE_SYSVSEM_SERIALIZE
        new_mutex->inter_meth = &mutex_sysv_methods;
#elif APR_USE_FCNTL_SERIALIZE
        new_mutex->inter_meth = &mutex_fcntl_methods;
#elif APR_USE_PROC_PTHREAD_SERIALIZE
        new_mutex->inter_meth = &mutex_proc_pthread_methods;
#elif APR_USE_POSIXSEM_SERIALIZE
        new_mutex->inter_meth = &mutex_posixsem_methods;
#else
        return APR_ENOTIMPL;
#endif
        break;
    default:
        return APR_ENOTIMPL;
    }
    return APR_SUCCESS;
}

APR_DECLARE(const char *) apr_proc_mutex_defname(void)
{
    apr_status_t rv;
    apr_proc_mutex_t mutex;

    if ((rv = proc_mutex_choose_method(&mutex, APR_LOCK_DEFAULT)) != APR_SUCCESS) {
        return "unknown";
    }
    mutex.meth = mutex.inter_meth;

    return apr_proc_mutex_name(&mutex);
}
   
static apr_status_t proc_mutex_create(apr_proc_mutex_t *new_mutex, apr_lockmech_e mech, const char *fname)
{
    apr_status_t rv;

    if ((rv = proc_mutex_choose_method(new_mutex, mech)) != APR_SUCCESS) {
        return rv;
    }

    new_mutex->meth = new_mutex->inter_meth;

    if ((rv = new_mutex->meth->create(new_mutex, fname)) != APR_SUCCESS) {
        return rv;
    }

    return APR_SUCCESS;
}

APR_DECLARE(apr_status_t) apr_proc_mutex_create(apr_proc_mutex_t **mutex,
                                                const char *fname,
                                                apr_lockmech_e mech,
                                                apr_pool_t *pool)
{
    apr_proc_mutex_t *new_mutex;
    apr_status_t rv;

    new_mutex = apr_pcalloc(pool, sizeof(apr_proc_mutex_t));
    new_mutex->pool = pool;

    if ((rv = proc_mutex_create(new_mutex, mech, fname)) != APR_SUCCESS)
        return rv;

    *mutex = new_mutex;
    return APR_SUCCESS;
}

APR_DECLARE(apr_status_t) apr_proc_mutex_child_init(apr_proc_mutex_t **mutex,
                                                    const char *fname,
                                                    apr_pool_t *pool)
{
    return (*mutex)->meth->child_init(mutex, pool, fname);
}

APR_DECLARE(apr_status_t) apr_proc_mutex_lock(apr_proc_mutex_t *mutex)
{
    return mutex->meth->acquire(mutex);
}

APR_DECLARE(apr_status_t) apr_proc_mutex_trylock(apr_proc_mutex_t *mutex)
{
    return mutex->meth->tryacquire(mutex);
}

APR_DECLARE(apr_status_t) apr_proc_mutex_unlock(apr_proc_mutex_t *mutex)
{
    return mutex->meth->release(mutex);
}

APR_DECLARE(apr_status_t) apr_proc_mutex_cleanup(void *mutex)
{
    return ((apr_proc_mutex_t *)mutex)->meth->cleanup(mutex);
}

APR_DECLARE(const char *) apr_proc_mutex_name(apr_proc_mutex_t *mutex)
{
    return mutex->meth->name;
}

APR_DECLARE(const char *) apr_proc_mutex_lockfile(apr_proc_mutex_t *mutex)
{
    /* POSIX sems use the fname field but don't use a file,
     * so be careful. */
#if APR_HAS_FLOCK_SERIALIZE
    if (mutex->meth == &mutex_flock_methods) {
        return mutex->fname;
    }
#endif
#if APR_HAS_FCNTL_SERIALIZE
    if (mutex->meth == &mutex_fcntl_methods) {
        return mutex->fname;
    }
#endif
    return NULL;
}

APR_POOL_IMPLEMENT_ACCESSOR(proc_mutex)

/* Implement OS-specific accessors defined in apr_portable.h */

APR_DECLARE(apr_status_t) apr_os_proc_mutex_get(apr_os_proc_mutex_t *ospmutex,
                                                apr_proc_mutex_t *pmutex)
{
#if APR_HAS_SYSVSEM_SERIALIZE || APR_HAS_FCNTL_SERIALIZE || APR_HAS_FLOCK_SERIALIZE || APR_HAS_POSIXSEM_SERIALIZE
    ospmutex->crossproc = pmutex->interproc->filedes;
#endif
#if APR_HAS_PROC_PTHREAD_SERIALIZE
    ospmutex->pthread_interproc = pmutex->pthread_interproc;
#endif
    return APR_SUCCESS;
}

APR_DECLARE(apr_status_t) apr_os_proc_mutex_put(apr_proc_mutex_t **pmutex,
                                                apr_os_proc_mutex_t *ospmutex,
                                                apr_pool_t *pool)
{
    if (pool == NULL) {
        return APR_ENOPOOL;
    }
    if ((*pmutex) == NULL) {
        (*pmutex) = (apr_proc_mutex_t *)apr_pcalloc(pool,
                                                    sizeof(apr_proc_mutex_t));
        (*pmutex)->pool = pool;
    }
#if APR_HAS_SYSVSEM_SERIALIZE || APR_HAS_FCNTL_SERIALIZE || APR_HAS_FLOCK_SERIALIZE || APR_HAS_POSIXSEM_SERIALIZE
    apr_os_file_put(&(*pmutex)->interproc, &ospmutex->crossproc, 0, pool);
#endif
#if APR_HAS_PROC_PTHREAD_SERIALIZE
    (*pmutex)->pthread_interproc = ospmutex->pthread_interproc;
#endif
    return APR_SUCCESS;
}