           && ap_strcmp_match(error, ssl_log_annotate[i].cpPattern) != 0)
        i++;

    return ssl_log_annotate[i].cpAnnotation;
}

void ssl_die(server_rec *s)
{
    if (s != NULL && s->is_virtual && s->error_fname != NULL)
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, NULL, APLOGNO(02311)
                     "Fatal error initialising mod_ssl, exiting. "
                     "See %s for more information",
                     ap_server_root_relative(s->process->pool,
                                             s->error_fname));
    else
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, NULL, APLOGNO(02312)
                     "Fatal error initialising mod_ssl, exiting.");

    /*
     * This is used for fatal errors and here
     * it is common module practice to really
     * exit from the complete program.
     * XXX: The config hooks should return errors instead of calling exit().
     */
    exit(1);
}

/*
 * Prints the SSL library error information.
 */
void ssl_log_ssl_error(const char *file, int line, int level, server_rec *s)
