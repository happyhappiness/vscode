            ufrag = 1;
        }
        apr_file_printf(errfile, "unsolicited size %d.%d%c" APR_EOL_STR,
                        (int)(unsolicited), (int)(ufrag), utype);
     }
     apr_file_printf(errfile, "size limit %d.0%c" APR_EOL_STR,
                     (int)(max), mtype);
     apr_file_printf(errfile, "total size was %d.%d%c, total size now "
                              "%d.%d%c" APR_EOL_STR,
                     (int)(total), (int)(tfrag), ttype, (int)(sum),
                     (int)(sfrag), stype);
     apr_file_printf(errfile, "total entries was %d, total entries now %d"
                              APR_EOL_STR, (int)(etotal), (int)(entries));
}

/*
 * delete a single file
 */
static void delete_file(char *path, char *basename, apr_pool_t *pool)
