static void simple_kill_random_child(simple_core_t * sc)
{
    /* See comment in simple_spawn_child for why we check here. */
    if (!sc->run_single_process) {
        apr_hash_index_t *hi;
        simple_child_t *child = NULL;

        apr_thread_mutex_lock(sc->mtx);
        hi = apr_hash_first(sc->pool, sc->children);
        if (hi != NULL) {
            apr_hash_this(hi, NULL, NULL, (void **)&child); 
            apr_hash_set(sc->children, &child->pid, sizeof(child->pid), NULL);
        }
        apr_thread_mutex_unlock(sc->mtx);
        
        if (child != NULL) {
            kill(child->pid, 9);
            /* TODO: recycle child object */
        }
    }
}