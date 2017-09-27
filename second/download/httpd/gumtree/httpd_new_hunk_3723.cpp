                                                AP_MODE_READBYTES,
                                                APR_BLOCK_READ,
                                                maxsize - AJP_HEADER_SZ);
                        if (status != APR_SUCCESS) {
                            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00880)
                                          "ap_get_brigade failed");
                            if (APR_STATUS_IS_TIMEUP(status)) {
                                rv = HTTP_REQUEST_TIME_OUT;
                            }
                            else if (status == AP_FILTER_ERROR) {
                                rv = AP_FILTER_ERROR;
                            }
                            client_failed = 1;
                            break;
                        }
                        bufsiz = maxsize;
                        status = apr_brigade_flatten(input_brigade, buff,
                                                     &bufsiz);
                        apr_brigade_cleanup(input_brigade);
                        if (status != APR_SUCCESS) {
                            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00881)
                                         "apr_brigade_flatten failed");
                            rv = HTTP_INTERNAL_SERVER_ERROR;
                            client_failed = 1;
                            break;
                        }
                    }

                    ajp_msg_reset(msg);
                    /* will go in ajp_send_data_msg */
