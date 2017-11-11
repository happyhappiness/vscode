static int log_debug_map_to_storage(request_rec *r)
{
    do_debug_log(r, hooks[4]);
    return DECLINED;
}