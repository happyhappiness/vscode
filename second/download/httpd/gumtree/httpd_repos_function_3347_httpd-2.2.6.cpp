apr_status_t apr_netware_proc_cleanup(void *theproc)
{
    apr_proc_t *proc = theproc;
    int exit_int;
    int waitpid_options = WUNTRACED | WNOHANG;

    if (proc->pid > 0) {
        waitpid(proc->pid, &exit_int, waitpid_options);
    }

/*	NXVmDestroy(proc->pid); */
    return APR_SUCCESS;
}