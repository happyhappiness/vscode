                         "Child %d: setup_inherited_listeners(), WSASocket failed to open the inherited socket.", my_pid);
            exit(APEXIT_CHILDINIT);
        }
        apr_os_sock_put(&lr->sd, &nsd, s->process->pool);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, ap_server_conf,
                 "Child %d: retrieved %d listeners from parent", my_pid, lcnt);

    if (!set_listeners_noninheritable(s->process->pool)) {
        exit(APEXIT_CHILDINIT);
    }
}
