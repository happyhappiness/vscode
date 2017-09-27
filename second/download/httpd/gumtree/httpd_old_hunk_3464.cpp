    }

    ap_pid_fname = arg;
    return NULL;
}

int ap_max_requests_per_child = 0;

const char *ap_mpm_set_max_requests(cmd_parms *cmd, void *dummy,
                                    const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_max_requests_per_child = atoi(arg);

    return NULL;
}

char ap_coredump_dir[MAX_STRING_LEN];
int ap_coredumpdir_configured;

const char *ap_mpm_set_coredumpdir(cmd_parms *cmd, void *dummy,
                                   const char *arg)
{
    apr_finfo_t finfo;
    const char *fname;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
