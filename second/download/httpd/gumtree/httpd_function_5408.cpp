static void end_gen(mpm_gen_info_t *gi)
{
    ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, ap_server_conf,
                 "end of generation %d", gi->gen);
    ap_run_end_generation(ap_server_conf, gi->gen);
    APR_RING_REMOVE(gi, link);
    APR_RING_INSERT_HEAD(unused_geninfo, gi, mpm_gen_info_t, link);
}