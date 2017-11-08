static int simple_spawn_child(simple_core_t * sc)
{
    pid_t pid = 0;
    int rv = 0;
    /* Although we could cut this off 'earlier', and not even invoke this 
     * function, I would like to keep the functions invoked when in debug mode
     * to be as close as possible to those when not in debug... So, we just skip
     * the actual spawn itself, but go through all of the motions...
     */
    if (!sc->run_single_process) {
        if (sc->spawn_via == SIMPLE_SPAWN_FORK) {
            
            pid = fork();
            if (pid == -1) {
                rv = errno;
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                             "simple_spawn_child: Unable to fork new process");
                return rv;
            }
            
            if (pid == 0) {
                /* this is the child process */
                
                rv = simple_child_loop(sc);

                if (rv) {
                    clean_child_exit(APEXIT_CHILDFATAL);
                }
                else {
                    clean_child_exit(0);
                }
            }
        }
        else {
            /* TODO: SIMPLE_SPAWN_EXEC */
            abort();
        }
    }

    if (pid != 0) {
        simple_child_t *child;

        apr_thread_mutex_lock(sc->mtx);

        child = apr_palloc(sc->pool, sizeof(simple_child_t));
        child->pid = pid;
        apr_hash_set(sc->children, &child->pid, sizeof(child->pid), child);

        apr_thread_mutex_unlock(sc->mtx);
    }
    
    return 0;
}