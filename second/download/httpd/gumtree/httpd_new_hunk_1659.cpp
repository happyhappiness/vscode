            }

            cpT = lookup_map(r, mapname, mapkey);
            if (cpT != NULL) {
                n = strlen(cpT);
                if (cpO + n >= newuri + sizeof(newuri)) {
                    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,
                                 r, "insufficient space in "
                                 "expand_map_lookups, aborting");
                    return;
                }
                memcpy(cpO, cpT, n);
                cpO += n;
            }
            else {
                n = strlen(defaultvalue);
                if (cpO + n >= newuri + sizeof(newuri)) {
                    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 
                                 r, "insufficient space in "
                                 "expand_map_lookups, aborting");
                    return;
                }
                memcpy(cpO, defaultvalue, n);
                cpO += n;
            }
