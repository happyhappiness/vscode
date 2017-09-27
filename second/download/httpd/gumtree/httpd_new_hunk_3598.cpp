    debug(fprintf(stderr, "macro_section: location=%s\n", macro->location));

    where =
        apr_psprintf(pool, "macro '%s' (%s)", macro->name, macro->location);

    if (looks_like_an_argument(name)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL, APLOGNO(02803)
                     "%s better prefix a macro name with any of '%s'",
                     where, ARG_PREFIX);
    }

    /* get macro parameters */
    macro->arguments = get_arguments(pool, arg);
