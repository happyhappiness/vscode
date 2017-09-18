#ifdef HAVE_TIMES
                               ws_record->times.tms_utime / tick,
                               ws_record->times.tms_stime / tick,
                               ws_record->times.tms_cutime / tick,
                               ws_record->times.tms_cstime / tick,
#endif
                               (long)((nowtime - ws_record->last_used) /
                                      APR_USEC_PER_SEC),
                               (long) req_time);

                    format_byte_out(r, conn_bytes);
                    ap_rputs("|", r);
                    format_byte_out(r, my_bytes);
                    ap_rputs("|", r);
