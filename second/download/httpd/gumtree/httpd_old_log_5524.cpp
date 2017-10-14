apr_file_printf(errfile, "total size was %d.%d%c, total size now "
                              "%d.%d%c" APR_EOL_STR,
                     (int)(s->total), (int)(tfrag), ttype,
                     (int)(s->sum), (int)(sfrag), stype);