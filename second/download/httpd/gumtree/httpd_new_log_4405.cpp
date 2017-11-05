ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, parms->temp_pool,
                          APLOGNO(02296) "Unknown directive %s "
                          "perhaps misspelled or defined by a module "
                          "not included in the server configuration", dir);