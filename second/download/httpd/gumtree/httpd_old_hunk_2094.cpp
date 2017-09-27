                    worker_thread_count);
            apr_thread_yield();
        }
        printf ("\nRestarting...\n");
    }

    return 0;
}

static int netware_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    int debug;
