                                   (void *)wl->data, w->pool);
            }
            wl = wl->next;
        }
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, wd_server_conf->s,
                 "%sWatchdog (%s) stopping (%" APR_PID_T_FMT ")",
                 w->singleton ? "Singleton" : "",
                 w->name, getpid());

    if (locked)
        apr_proc_mutex_unlock(w->mutex);
    apr_thread_exit(w->thread, APR_SUCCESS);

    return NULL;
