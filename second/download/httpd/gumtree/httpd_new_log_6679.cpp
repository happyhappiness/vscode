ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, 
                    "Websocket: SSL Frame contained %lu bytes, "\
                            "pushed to Lua stack", 
                        remaining);