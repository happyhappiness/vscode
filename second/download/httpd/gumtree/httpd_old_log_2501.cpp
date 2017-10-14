apr_file_printf(errfile, "total size was %d.%d%c, total size now "
                              "%d.%d%c" APR_EOL_STR,
                     (int)(total), (int)(tfrag), ttype, (int)(sum),
                     (int)(sfrag), stype);