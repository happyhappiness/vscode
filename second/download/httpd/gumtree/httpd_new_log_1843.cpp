ap_log_cerror(file, line, APLOG_MODULE_INDEX, level, rv, c,
                  "%s [subject: %s, issuer: %s, serial: %s]",
                  buf,
                  sname ? sname : "-unknown-",
                  iname ? iname : "-unknown-",
                  serial ? serial : "-unknown-");