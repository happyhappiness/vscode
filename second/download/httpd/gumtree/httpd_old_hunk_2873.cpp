                                      cmd_rewritecond_setflag)) != NULL) {
            return apr_pstrcat(cmd->pool, "RewriteCond: ", err, NULL);
        }
    }

    /* arg2: the pattern */
    if (*a2 == '!') {
        newcond->flags |= CONDFLAG_NOTMATCH;
        ++a2;
    }

    /* determine the pattern type */
    newcond->ptype = 0;
    if (*a2 && a2[1]) {
        if (!a2[2] && *a2 == '-') {
            switch (a2[1]) {
            case 'f': newcond->ptype = CONDPAT_FILE_EXISTS; break;
            case 's': newcond->ptype = CONDPAT_FILE_SIZE;   break;
            case 'l': newcond->ptype = CONDPAT_FILE_LINK;   break;
            case 'd': newcond->ptype = CONDPAT_FILE_DIR;    break;
            case 'x': newcond->ptype = CONDPAT_FILE_XBIT;   break;
            case 'U': newcond->ptype = CONDPAT_LU_URL;      break;
            case 'F': newcond->ptype = CONDPAT_LU_FILE;     break;
            }
        }
        else {
            switch (*a2) {
            case '>': newcond->ptype = CONDPAT_STR_GT; break;
            case '<': newcond->ptype = CONDPAT_STR_LT; break;
            case '=': newcond->ptype = CONDPAT_STR_EQ;
                /* "" represents an empty string */
                if (*++a2 == '"' && a2[1] == '"' && !a2[2]) {
                    a2 += 2;
                }
                break;
            }
        }
    }

    if (newcond->ptype && newcond->ptype != CONDPAT_STR_EQ &&
        (newcond->flags & CONDFLAG_NOCASE)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                     "RewriteCond: NoCase option for non-regex pattern '%s' "
                     "is not supported and will be ignored.", a2);
        newcond->flags &= ~CONDFLAG_NOCASE;
    }

    newcond->pattern = a2;

    if (!newcond->ptype) {
        regexp = ap_pregcomp(cmd->pool, a2,
                             AP_REG_EXTENDED | ((newcond->flags & CONDFLAG_NOCASE)
                                             ? AP_REG_ICASE : 0));
        if (!regexp) {
            return apr_pstrcat(cmd->pool, "RewriteCond: cannot compile regular "
                               "expression '", a2, "'", NULL);
        }

        newcond->regexp  = regexp;
    }

    return NULL;
}

static const char *cmd_rewriterule_setflag(apr_pool_t *p, void *_cfg,
                                           char *key, char *val)
