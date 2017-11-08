static int log_debug_type_checker(request_rec *r)
{
    do_debug_log(r, hooks[6]);
    return DECLINED;
}