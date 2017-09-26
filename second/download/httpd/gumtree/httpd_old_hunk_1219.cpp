        apr_ctime(timestamp, apr_time_now());
        apr_file_open_stderr(&se, dbc->pool);
        apr_file_printf(se, "[%s] %s\n", timestamp, dbc->lastError);
    }
}

/*
*   public functions per DBD driver API
*/

/** init: allow driver to perform once-only initialisation. **/
static void odbc_init(apr_pool_t *pool)
