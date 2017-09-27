
    if (err != NULL) {
        return err;
    }

    ap_min_spare_threads = atoi(arg);
    return NULL;
}



static const char *set_max_spare_threads(cmd_parms *cmd, void *dummy,
