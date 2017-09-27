            }
        }
        apr_os_sock_put(&lr->sd, &nsd, s->process->pool);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                 "Child %lu: retrieved %d listeners from parent", my_pid, lcnt);
}


static int send_listeners_to_child(apr_pool_t *p, DWORD dwProcessId,
                                   apr_file_t *child_in)
{
