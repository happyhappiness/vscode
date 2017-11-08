int main(int argc, const char * const argv[])
{
    apr_pool_t *p;
    int i = 0;
    apr_lockmech_e mech;
    apr_global_mutex_t *global_lock;
    apr_status_t rv;

    apr_initialize();
    atexit(apr_terminate);
    
    apr_pool_create(&p, NULL);
    if (argc >= 2) {
        mech = (apr_lockmech_e)apr_strtoi64(argv[1], NULL, 0);
    }
    else {
        mech = APR_LOCK_DEFAULT;
    }
    rv = apr_global_mutex_create(&global_lock, LOCKNAME, mech, p);
    if (rv != APR_SUCCESS) {
        exit(-rv);
    }
    apr_global_mutex_child_init(&global_lock, LOCKNAME, p);
    
    while (1) {
        apr_global_mutex_lock(global_lock);
        if (i == MAX_ITER) {
            apr_global_mutex_unlock(global_lock);
            exit(i);
        }
        i++;
        apr_global_mutex_unlock(global_lock);
    }
    exit(0);
}