void simple_check_children_size(simple_core_t * sc, void *baton)
{
    unsigned int count;
    int wanted;
    int i;

    simple_register_timer(sc,
                          simple_check_children_size,
                          NULL, SPAWN_CHILDREN_INTERVAL,
                          sc->pool);

    if (sc->run_single_process && sc->restart_num == 2) {
        static int run = 0;
        /* This is kinda of hack, but rather than spawning a child process, 
         * we register the normal IO handlers in the main event loop....
         */
        if (run == 0) {
            simple_single_process_hack(sc);
            run++;
        }
    }

    {
        apr_thread_mutex_lock(sc->mtx);
        count = apr_hash_count(sc->children);
        wanted = sc->procmgr.proc_count;
        apr_thread_mutex_unlock(sc->mtx);
    }

    if (count > wanted) {
        /* kill some kids */
        int to_kill = count - wanted;
        for (i = 0; i < to_kill; i++) {
            simple_kill_random_child(sc);
        }
    }
    else if (count < wanted) {
        int rv = 0;
        /* spawn some kids */
        int to_spawn = wanted - count;
        for (i = 0; rv == 0 && i < to_spawn; i++) {
            rv = simple_spawn_child(sc);
        }
    }
    else {
        /* juuuuust right. */
    }
}