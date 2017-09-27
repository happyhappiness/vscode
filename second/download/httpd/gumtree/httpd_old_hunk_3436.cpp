            *result = ap_daemons_limit;
            break;
        case AP_MPMQ_MPM_STATE:
            *result = mpm_state;
            break;
        case AP_MPMQ_GENERATION:
            *result = my_generation;
            break;
        default:
            *rv = APR_ENOTIMPL;
            break;
    }
    return OK;
}

static apr_status_t worker_note_child_killed(int childnum)
{
    ap_scoreboard_image->parent[childnum].pid = 0;
    return APR_SUCCESS;
}

static const char *worker_get_name(void)
{
    return "worker";
}
