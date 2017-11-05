static const char *set_proccount(cmd_parms * cmd, void *baton,
                                 const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    simple_core_get()->procmgr.proc_count = atoi(arg);
    return NULL;
}