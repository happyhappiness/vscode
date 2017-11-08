static int log_debug_check_authz(request_rec *r)
{
    do_debug_log(r, hooks[10]);
    return DECLINED;
}