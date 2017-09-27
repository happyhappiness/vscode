ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, 
                    "Websocket: SSL Frame contained %" APR_SIZE_T_FMT " bytes, "\
                            "pushed to Lua stack", 
                        remaining);