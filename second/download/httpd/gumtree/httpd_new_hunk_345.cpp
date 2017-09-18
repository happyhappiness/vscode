            break;
        }
    }
    return errstr;
}

void ssl_die(void)
{
    /*
     * This is used for fatal errors and here
     * it is common module practice to really
     * exit from the complete program.
     */
    exit(1);
}

/*
 * Prints the SSL library error information.
 */
void ssl_log_ssl_error(const char *file, int line, int level, server_rec *s)
{
    unsigned long e;

    while ((e = ERR_get_error())) {
        char *err, *annotation;
        err = ERR_error_string(e, NULL);
        annotation = ssl_log_annotation(err);

        if (annotation) {
            ap_log_error(file, line, level, 0, s,
                         "SSL Library Error: %ld %s %s",
                         e, err, annotation); 
        }
        else {
            ap_log_error(file, line, level, 0, s,
                         "SSL Library Error: %ld %s",
                         e, err); 
        }
    }
}
