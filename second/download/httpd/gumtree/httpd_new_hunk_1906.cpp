        }
    }

    endgrent();

    return setgroups(index, groups);
#endif
}
#endif /* def NEED_INITGROUPS */

/* standard mpm configuration handling */
const char *ap_pid_fname = NULL;

const char *ap_mpm_set_pidfile(cmd_parms *cmd, void *dummy,
                               const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
