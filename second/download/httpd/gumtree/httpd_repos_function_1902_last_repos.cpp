static const char *multiviews_match(cmd_parms *cmd, void *m_,
                                    const char *include)
{
    mime_dir_config *m = (mime_dir_config *) m_;
    const char *errmsg;

    errmsg = ap_check_cmd_context(cmd, NOT_IN_LOCATION);
    if (errmsg != NULL) {
        return errmsg;
    }

    if (strcasecmp(include, "Any") == 0) {
        if (m->multimatch && (m->multimatch & ~MULTIMATCH_ANY)) {
            return "Any is incompatible with NegotiatedOnly, "
                   "Filters and Handlers";
        }
        m->multimatch |= MULTIMATCH_ANY;
    }
    else if (strcasecmp(include, "NegotiatedOnly") == 0) {
        if (m->multimatch && (m->multimatch & ~MULTIMATCH_NEGOTIATED)) {
            return "NegotiatedOnly is incompatible with Any, "
                   "Filters and Handlers";
        }
        m->multimatch |= MULTIMATCH_NEGOTIATED;
    }
    else if (strcasecmp(include, "Filters") == 0) {
        if (m->multimatch && (m->multimatch & (MULTIMATCH_NEGOTIATED
                                             | MULTIMATCH_ANY))) {
            return "Filters is incompatible with Any and NegotiatedOnly";
        }
        m->multimatch |= MULTIMATCH_FILTERS;
    }
    else if (strcasecmp(include, "Handlers") == 0) {
        if (m->multimatch && (m->multimatch & (MULTIMATCH_NEGOTIATED
                                             | MULTIMATCH_ANY))) {
            return "Handlers is incompatible with Any and NegotiatedOnly";
        }
        m->multimatch |= MULTIMATCH_HANDLERS;
    }
    else {
        return apr_psprintf(cmd->pool, "Unrecognized option '%s'", include);
    }

    return NULL;
}