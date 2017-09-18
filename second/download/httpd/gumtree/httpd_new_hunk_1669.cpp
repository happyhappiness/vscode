    char *loc;
    time_t nowtime = time(NULL);
    time_t up_time;
    int i, res;
    int ready = 0;
    int busy = 0;
    unsigned long count = 0;
    unsigned long lres, bytes;
    unsigned long my_lres, my_bytes, conn_bytes;
    unsigned short conn_lres;
    unsigned long bcount = 0;
    unsigned long kbcount = 0;
    long req_time;
#if defined(NEXT)
    float tick = HZ;
#elif !defined(NO_TIMES)
    float tick = sysconf(_SC_CLK_TCK);
#endif
    int short_report = 0;
    int no_table_report = 0;
    short_score score_record;
    parent_score ps_record;
    char stat_buffer[HARD_SERVER_LIMIT];
    int pid_buffer[HARD_SERVER_LIMIT];
    clock_t tu, ts, tcu, tcs;

    tu = ts = tcu = tcs = 0;

    if (!ap_exists_scoreboard_image()) {
	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		    "Server status unavailable in inetd mode");
	return HTTP_INTERNAL_SERVER_ERROR;
    }
    r->allowed = (1 << M_GET);
    if (r->method_number != M_GET)
	return DECLINED;
