static int log_debug_check_access_ex(request_rec *r)
{
    do_debug_log(r, hooks[8]);
    return DECLINED;
}