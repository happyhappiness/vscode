ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02318)
                          "Error: authz provider %s: invalid return value %d",
                          prov_spec->name, result);