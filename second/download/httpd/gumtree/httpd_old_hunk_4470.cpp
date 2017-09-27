                             apr_atomic_read32(&connection_count),
                             apr_atomic_read32(&clogged_count),
                             *write_completion_q->total,
                             *keepalive_q->total,
                             apr_atomic_read32(&lingering_count),
                             apr_atomic_read32(&suspended_count));
                apr_thread_mutex_unlock(timeout_mutex);
            }
        }

        apr_thread_mutex_lock(g_timer_skiplist_mtx);
        te = apr_skiplist_peek(timer_skiplist);
