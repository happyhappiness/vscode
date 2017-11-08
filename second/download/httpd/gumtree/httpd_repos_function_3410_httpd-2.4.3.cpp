static const char *set_worker_factor(cmd_parms * cmd, void *dummy,
                                     const char *arg)
{
    double val;
    char *endptr;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    val = strtod(arg, &endptr);
    if (*endptr)
        return "error parsing value";

    worker_factor = val * WORKER_FACTOR_SCALE;
    if (worker_factor == 0)
        worker_factor = 1;
    return NULL;
}