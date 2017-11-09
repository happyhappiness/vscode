static int log_debug_handler(request_rec *r)
{
    do_debug_log(r, hooks[2]);
    return DECLINED;
}