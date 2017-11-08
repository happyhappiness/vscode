static int log_debug_quick_handler(request_rec *r, int lookup_uri)
{
    do_debug_log(r, hooks[1]);
    return DECLINED;
}