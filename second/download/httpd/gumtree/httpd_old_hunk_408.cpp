}

#if !defined (RLIMIT_CPU) || !(defined (RLIMIT_DATA) || defined (RLIMIT_VMEM) || defined(RLIMIT_AS)) || !defined (RLIMIT_NPROC)
static const char *no_set_limit(cmd_parms *cmd, void *conf_,
                                const char *arg, const char *arg2)
{
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, cmd->server,
                "%s not supported on this platform", cmd->cmd->name);

    return NULL;
}
#endif

