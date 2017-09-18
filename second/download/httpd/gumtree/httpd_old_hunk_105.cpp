            }
            else if (!strcmp(tag, "encoding")) {
                if (!strcasecmp(tag_val, "none")) encode = E_NONE;
                else if (!strcasecmp(tag_val, "url")) encode = E_URL;
                else if (!strcasecmp(tag_val, "entity")) encode = E_ENTITY;
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                           "unknown value \"%s\" to parameter \"encoding\" of "
                           "tag echo in %s", tag_val, r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                }
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" in tag echo of %s",
                            tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
            }

        }
