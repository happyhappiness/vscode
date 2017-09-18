                    *inserted_head = tmp_buck;
                }
            }
            return 0;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "printenv directive does not take tags in %s", 
                        r->filename);
            CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
            return -1;
        }
    }
