static char *ssl_log_annotation(char *error)
{
    char *errstr;
    int i;

    errstr = NULL;
    for (i = 0; ssl_log_annotate[i].cpPattern != NULL; i++) {
        if (ap_strcmp_match(error, ssl_log_annotate[i].cpPattern) == 0) {
            errstr = ssl_log_annotate[i].cpAnnotation;
            break;
        }
    }
    return errstr;
}