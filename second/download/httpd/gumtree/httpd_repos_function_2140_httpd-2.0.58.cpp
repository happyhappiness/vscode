static const char *set_thread_stacksize(cmd_parms *cmd, void *dummy, 
                                        const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }
    
    ap_thread_stack_size = atoi(arg);
    return NULL;
}