
                this->mutex.type = apr_anylock_threadmutex;
                rv = apr_thread_mutex_create(&this->mutex.lock.tm,
                                             APR_THREAD_MUTEX_DEFAULT,
                                             p);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                                 "could not initialize buffered log mutex, "
                                 "transfer log may become corrupted");
                    this->mutex.type = apr_anylock_none;
                }
            }
            else
