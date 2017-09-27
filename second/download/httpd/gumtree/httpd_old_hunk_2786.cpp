                        cp++;
                    }
                    else if (*cp == '\0' || *cp == ';') {
                        break;
                    }
                    else {
                        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                                     "Cannot get media parameter.");
                        return (NULL);
                    }
                }
            }
            value = zap_sp_and_dup(p, mp, cp, NULL);
            if (value == NULL || *value == '\0') {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                             "Cannot get media parameter.");
                return (NULL);
            }

            pp = apr_palloc(p, sizeof(param));
            pp->attr = attribute;
