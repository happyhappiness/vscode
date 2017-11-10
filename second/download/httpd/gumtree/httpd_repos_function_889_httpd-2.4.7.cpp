static const char *ssl_log_annotation(const char *error)
{
    int i = 0;

    while (ssl_log_annotate[i].cpPattern != NULL
           && ap_strcmp_match(error, ssl_log_annotate[i].cpPattern) != 0)
        i++;

    return ssl_log_annotate[i].cpAnnotation;
}