                                      cmd_rewritecond_setflag)) != NULL) {
            return apr_pstrcat(cmd->pool, "RewriteCond: ", err, NULL);
        }
    }

    /* arg2: the pattern */
    newcond->pattern = a2;
    if (*a2 == '!') {
        newcond->flags |= CONDFLAG_NOTMATCH;
        ++a2;
    }

    /* determine the pattern type */
    newcond->ptype = CONDPAT_REGEX;
    if (strcasecmp(a1, "expr") == 0) {
        newcond->ptype = CONDPAT_AP_EXPR;
    }
    else if (*a2 && a2[1]) {
        if (!a2[2] && *a2 == '-') {
            switch (a2[1]) {
            case 'f': newcond->ptype = CONDPAT_FILE_EXISTS; break;
            case 's': newcond->ptype = CONDPAT_FILE_SIZE;   break;
            case 'd': newcond->ptype = CONDPAT_FILE_DIR;    break;
            case 'x': newcond->ptype = CONDPAT_FILE_XBIT;   break;
            case 'h': newcond->ptype = CONDPAT_FILE_LINK;   break;
            case 'L': newcond->ptype = CONDPAT_FILE_LINK;   break;
            case 'U': newcond->ptype = CONDPAT_LU_URL;      break;
            case 'F': newcond->ptype = CONDPAT_LU_FILE;     break;
            case 'l': if (a2[2] == 't')
                          a2 += 3, newcond->ptype = CONDPAT_INT_LT;
                      else if (a2[2] == 'e')
                          a2 += 3, newcond->ptype = CONDPAT_INT_LE;
                      else /* Historical; prefer -L or -h instead */
                          newcond->ptype = CONDPAT_FILE_LINK;
                      break;
            case 'g': if (a2[2] == 't')
                          a2 += 3, newcond->ptype = CONDPAT_INT_GT;
                      else if (a2[2] == 'e')
                          a2 += 3, newcond->ptype = CONDPAT_INT_GE;
                      break;
            case 'e': if (a2[2] == 'q')
                          a2 += 3, newcond->ptype = CONDPAT_INT_EQ;
                      break;
            case 'n': if (a2[2] == 'e') {
                          /* Inversion, ensure !-ne == -eq */
                          a2 += 3, newcond->ptype = CONDPAT_INT_EQ;
                          newcond->flags ^= CONDFLAG_NOTMATCH;
                      }
                      break;
            }
        }
        else {
            switch (*a2) {
            case '>': if (*++a2 == '=')
                          ++a2, newcond->ptype = CONDPAT_STR_GE;
                      else
                          newcond->ptype = CONDPAT_STR_GT;
                      break;

            case '<': if (*++a2 == '=')
                          ++a2, newcond->ptype = CONDPAT_STR_LE;
                      else
                          newcond->ptype = CONDPAT_STR_LT;
                      break;

            case '=': newcond->ptype = CONDPAT_STR_EQ;
                      /* "" represents an empty string */
                      if (*++a2 == '"' && a2[1] == '"' && !a2[2])
                          a2 += 2;
                      break;
            }
        }
    }

    if ((newcond->ptype != CONDPAT_REGEX) &&
        (newcond->ptype < CONDPAT_STR_LT || newcond->ptype > CONDPAT_STR_GE) &&
        (newcond->flags & CONDFLAG_NOCASE)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00665)
                     "RewriteCond: NoCase option for non-regex pattern '%s' "
                     "is not supported and will be ignored. (%s:%d)", a2,
                     cmd->directive->filename, cmd->directive->line_num);
        newcond->flags &= ~CONDFLAG_NOCASE;
    }

    newcond->pskip = a2 - newcond->pattern;
    newcond->pattern += newcond->pskip;

    if (newcond->ptype == CONDPAT_REGEX) {
        regexp = ap_pregcomp(cmd->pool, a2,
                             AP_REG_EXTENDED | ((newcond->flags & CONDFLAG_NOCASE)
                                             ? AP_REG_ICASE : 0));
        if (!regexp) {
            return apr_pstrcat(cmd->pool, "RewriteCond: cannot compile regular "
                               "expression '", a2, "'", NULL);
        }

        newcond->regexp  = regexp;
    }
    else if (newcond->ptype == CONDPAT_AP_EXPR) {
        unsigned int flags = newcond->flags & CONDFLAG_NOVARY ?
                             AP_EXPR_FLAG_DONT_VARY : 0;
        newcond->expr = ap_expr_parse_cmd(cmd, a2, flags, &err, NULL);
        if (err)
            return apr_psprintf(cmd->pool, "RewriteCond: cannot compile "
                                "expression \"%s\": %s", a2, err);
    }

    return NULL;
}

static const char *cmd_rewriterule_setflag(apr_pool_t *p, void *_cfg,
                                           char *key, char *val)
