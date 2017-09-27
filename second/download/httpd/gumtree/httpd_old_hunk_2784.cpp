                cp++;
                continue;
            }
            else if (*cp == '=') {
                attribute = zap_sp_and_dup(p, mp, cp, NULL);
                if (attribute == NULL || *attribute == '\0') {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                                 "Cannot get media parameter.");
                    return (NULL);
                }
                cp++;
                cp = zap_sp(cp);
                if (cp == NULL || *cp == '\0') {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                                 "Cannot get media parameter.");
                    return (NULL);
                }
                mp = cp;
                continue;
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                             "Cannot get media parameter.");
                return (NULL);
            }
        }
        else {
            if (mp == cp) {
