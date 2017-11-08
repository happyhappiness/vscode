static apr_status_t piped_log_cleanup(void *data)
{
    piped_log *pl = data;

    if (pl->pid != NULL) {
        apr_proc_kill(pl->pid, SIGTERM);
    }
    return piped_log_cleanup_for_exec(data);
}