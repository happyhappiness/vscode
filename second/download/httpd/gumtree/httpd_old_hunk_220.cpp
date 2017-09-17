{
    regex_t *compiled;
    int regex_error;

    compiled = ap_pregcomp(r->pool, rexp, REG_EXTENDED | REG_NOSUB);
    if (compiled == NULL) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "unable to compile pattern \"%s\"", rexp);
        return -1;
    }
    regex_error = regexec(compiled, string, 0, (regmatch_t *) NULL, 0);
    ap_pregfree(r->pool, compiled);
    return (!regex_error);
