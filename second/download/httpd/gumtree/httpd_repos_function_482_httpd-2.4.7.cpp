static int log_debug_check_access(request_rec *r)
{
    do_debug_log(r, hooks[7]);
    return DECLINED;
}