apr_file_printf(errfile, "%d entries deleted (%d from future, %d "
                              "expired, %d fresh)" APR_EOL_STR,
                     (int)(s->etotal - s->entries), (int)(s->dfuture),
                     (int)(s->dexpired), (int)(s->dfresh));