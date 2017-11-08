apr_status_t apr_netware_proc_cleanup(void *theproc)
{
    apr_proc_t *proc = theproc;

	NXVmDestroy(proc->pid);
    return APR_SUCCESS;
}