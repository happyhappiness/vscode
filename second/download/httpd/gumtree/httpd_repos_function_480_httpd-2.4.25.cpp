static int log_debug_fixups(request_rec *r)
{
    do_debug_log(r, hooks[5]);
    return DECLINED;
}