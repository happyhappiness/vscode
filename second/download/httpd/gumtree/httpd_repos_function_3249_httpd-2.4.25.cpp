static int x_pre_mpm(apr_pool_t *p, ap_scoreboard_e sb_type)
{
    trace_nocontext(p, __FILE__, __LINE__, "x_pre_mpm()");
    return DECLINED;
}