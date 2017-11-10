static const char *set_threadcount(cmd_parms * cmd, void *baton,
                                   const char *arg)
{
    simple_core_t *sc = simple_core_get();
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    sc->procmgr.thread_count = atoi(arg);

    return NULL;
}