apr_file_printf(
            errfile,
            "%" APR_OFF_T_FMT " entries deleted (%" APR_OFF_T_FMT " from future, %"
            APR_OFF_T_FMT " expired, %" APR_OFF_T_FMT " fresh)" APR_EOL_STR,
            (s->etotal - s->entries), s->dfuture, s->dexpired, s->dfresh);