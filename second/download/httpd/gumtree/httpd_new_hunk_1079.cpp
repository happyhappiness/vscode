        case AP_MPMQ_MAX_REQUESTS_DAEMON:
            *result = ap_max_requests_per_child;
            return APR_SUCCESS;
        case AP_MPMQ_MAX_DAEMONS:
            *result = ap_daemons_limit;
            return APR_SUCCESS;
        case AP_MPMQ_MPM_STATE:
            *result = mpm_state;
            return APR_SUCCESS;
    }
    return APR_ENOTIMPL;
}

/* a clean exit from a child with proper cleanup */ 
static void clean_child_exit(int code) __attribute__ ((noreturn));
static void clean_child_exit(int code)
{
    mpm_state = AP_MPMQ_STOPPING;
    if (pchild) {
        apr_pool_destroy(pchild);
    }
    ap_mpm_pod_close(pod);
    exit(code);
}

static void just_die(int sig)
{
    clean_child_exit(0);
}

/*****************************************************************
