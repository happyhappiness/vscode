        *result = ap_daemons_limit;
        break;
    case AP_MPMQ_MPM_STATE:
        *result = mpm_state;
        break;
    case AP_MPMQ_GENERATION:
        *result = retained->my_generation;
        break;
    default:
        *rv = APR_ENOTIMPL;
        break;
    }
    return OK;
}

static void event_note_child_killed(int childnum, pid_t pid, ap_generation_t gen)
{
    if (childnum != -1) { /* child had a scoreboard slot? */
        ap_run_child_status(ap_server_conf,
                            ap_scoreboard_image->parent[childnum].pid,
                            ap_scoreboard_image->parent[childnum].generation,
                            childnum, MPM_CHILD_EXITED);
        ap_scoreboard_image->parent[childnum].pid = 0;
    }
    else {
        ap_run_child_status(ap_server_conf, pid, gen, -1, MPM_CHILD_EXITED);
    }
}

static void event_note_child_started(int slot, pid_t pid)
{
    ap_scoreboard_image->parent[slot].pid = pid;
    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[slot].pid,
                        retained->my_generation, slot, MPM_CHILD_STARTED);
}

static void event_note_child_lost_slot(int slot, pid_t newpid)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00458)
                 "pid %" APR_PID_T_FMT " taking over scoreboard slot from "
                 "%" APR_PID_T_FMT "%s",
                 newpid,
                 ap_scoreboard_image->parent[slot].pid,
                 ap_scoreboard_image->parent[slot].quiescing ?
                 " (quiescing)" : "");
    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[slot].pid,
                        ap_scoreboard_image->parent[slot].generation,
                        slot, MPM_CHILD_LOST_SLOT);
    /* Don't forget about this exiting child process, or we
     * won't be able to kill it if it doesn't exit by the
     * time the server is shut down.
     */
    ap_register_extra_mpm_process(ap_scoreboard_image->parent[slot].pid,
                                  ap_scoreboard_image->parent[slot].generation);
}

static const char *event_get_name(void)
{
    return "event";
}
