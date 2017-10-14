apr_psprintf(r->pool, "%x:%lx:%x", getpid(), time(NULL),
                          apr_atomic_inc32(&next_id));