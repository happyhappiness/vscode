    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_threads_per_child = atoi(arg);
    if (ap_threads_per_child > HARD_SERVER_LIMIT) {
        fprintf(stderr, "WARNING: ThreadsPerChild of %d exceeds compile time limit "
                "of %d threads,\n", ap_threads_per_child, HARD_SERVER_LIMIT);
        fprintf(stderr, " lowering ThreadsPerChild to %d.  To increase, please "
                "see the\n", HARD_SERVER_LIMIT);
        fprintf(stderr, " HARD_SERVER_LIMIT define in src/include/httpd.h.\n");
        ap_threads_per_child = HARD_SERVER_LIMIT;
    } 
    else if (ap_threads_per_child < 1) {
	fprintf(stderr, "WARNING: Require ThreadsPerChild > 0, setting to 1\n");
	ap_threads_per_child = 1;
    }

    return NULL;
}

static const char *set_excess_requests(cmd_parms *cmd, void *dummy, char *arg) 
{
