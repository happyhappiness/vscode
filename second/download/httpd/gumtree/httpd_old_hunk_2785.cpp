                    else if (*cp == '"') {
                        cp++;
                        while (*cp == ' ' || *cp == '\t' || *cp == '\n') {
                            cp++;
                        }
                        if (*cp != ';' && *cp != '\0') {
                            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                                         "Cannot get media parameter.");
                            return(NULL);
                        }
                        quoted = 0;
                    }
                    else {
                        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                                     "Cannot get media parameter.");
                        return (NULL);
                    }
                }
            }
            else {
