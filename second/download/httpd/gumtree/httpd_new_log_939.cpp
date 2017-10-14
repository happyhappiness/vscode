apr_psprintf(p, "Syntax error on line %d of %s: %s",
                            parms.err_directive->line_num,
                            parms.err_directive->filename, error);