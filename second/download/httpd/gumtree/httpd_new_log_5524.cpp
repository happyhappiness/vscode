apr_file_printf(
            errfile,
            "total size was %" APR_OFF_T_FMT ".%" APR_OFF_T_FMT "%c, total size now "
            "%" APR_OFF_T_FMT ".%" APR_OFF_T_FMT "%c" APR_EOL_STR, s->total,
            tfrag, ttype, s->sum, sfrag, stype);