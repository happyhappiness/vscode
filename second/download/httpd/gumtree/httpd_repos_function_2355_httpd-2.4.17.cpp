void h2_task_die(h2_task_env *env, int status, request_rec *r)
{
    (void)env;
    ap_die(status, r);
}