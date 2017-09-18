                        return 1;
                    }
                }
                if (!strcmp(tag, "cmd")) {
                    cgid_pfn_ps(r, ctx, tag_val, parsed_string, sizeof(parsed_string), 1);
                    if (include_cmd(ctx, bb, parsed_string, r, f) == -1) {
                        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                                    "execution failure for parameter \"%s\" "
                                    "to tag exec in file %s", tag, r->filename);
                        CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                    }
                    /* just in case some stooge changed directories */
                }
