static const char *comp_urlmap(cmd_parms *cmd, urlmap *newmap,
                               const char *from, const char *to,
                               const char *flags, const char *cond)
{
    const char *err = NULL;
    newmap->flags
        = XREGFLAG(M_HTML,flags,'h')
        | XREGFLAG(M_EVENTS,flags,'e')
        | XREGFLAG(M_CDATA,flags,'c')
        | REGFLAG(M_ATSTART,flags,'^')
        | REGFLAG(M_ATEND,flags,'$')
        | REGFLAG(M_REGEX,flags,'R')
        | REGFLAG(M_LAST,flags,'L')
        | REGFLAG(M_NOTLAST,flags,'l')
        | REGFLAG(M_INTERPOLATE_TO,flags,'V')
        | REGFLAG(M_INTERPOLATE_FROM,flags,'v');

    if ((newmap->flags & M_INTERPOLATE_FROM) || !(newmap->flags & M_REGEX)) {
        newmap->from.c = from;
        newmap->to = to;
    }
    else {
        newmap->regflags
            = REGFLAG(AP_REG_EXTENDED,flags,'x')
            | REGFLAG(AP_REG_ICASE,flags,'i')
            | REGFLAG(AP_REG_NOSUB,flags,'n')
            | REGFLAG(AP_REG_NEWLINE,flags,'s');
        newmap->from.r = ap_pregcomp(cmd->pool, from, newmap->regflags);
        newmap->to = to;
    }
    if (cond != NULL) {
        /* back-compatibility: support old-style ENV expressions
         * by converting to ap_expr syntax.
         *
         * 1. var --> env(var)
         * 2. var=val --> env(var)=val
         * 3. !var --> !env(var)
         * 4. !var=val --> env(var)!=val
         */
        char *newcond = NULL;
        if (ap_rxplus_exec(cmd->temp_pool, old_expr, cond, &newcond)) {
           /* we got a substitution.  Check for the case (3) above
            * that the regexp gets wrong: a negation without a comparison.
            */
            if ((cond[0] == '!') && !ap_strchr_c(cond, '=')) {
                memmove(newcond+1, newcond, strlen(newcond)-1);
                newcond[0] = '!';
            }
            cond = newcond;
        }
        newmap->cond = ap_expr_parse_cmd(cmd, cond, 0, &err, NULL);
    }
    else {
        newmap->cond = NULL;
    }
    return err;
}