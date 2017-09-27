           && ap_strcmp_match(error, ssl_log_annotate[i].cpPattern) != 0)
        i++;

    return ssl_log_annotate[i].cpAnnotation;
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
