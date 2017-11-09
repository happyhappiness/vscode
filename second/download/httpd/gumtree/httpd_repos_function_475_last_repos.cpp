static int log_debug_log_transaction(request_rec *r)
{
    do_debug_log(r, hooks[0]);
    return DECLINED;
}