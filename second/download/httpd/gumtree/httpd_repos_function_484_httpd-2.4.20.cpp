static int log_debug_translate_name(request_rec *r)
{
    do_debug_log(r, hooks[3]);
    return DECLINED;
}