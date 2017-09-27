    }

    max_spare_threads = atoi(arg);
    return NULL;
}

static const char *set_max_clients(cmd_parms * cmd, void *dummy,
                                   const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    max_clients = atoi(arg);
    return NULL;
}

static const char *set_threads_per_child(cmd_parms * cmd, void *dummy,
                                         const char *arg)
{
