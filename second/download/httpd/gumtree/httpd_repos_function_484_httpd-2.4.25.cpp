static int log_debug_check_authn(request_rec *r)
{
    do_debug_log(r, hooks[9]);
    return DECLINED;
}