        if (max) {
            limit->rlim_max = max;
        }
    }
#else

    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, cmd->server,
                 "Platform does not support rlimit for %s", cmd->cmd->name);
#endif
}

APR_HOOK_STRUCT(
               APR_HOOK_LINK(get_suexec_identity)
