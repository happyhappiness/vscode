const char *table_strerror(const int error)
{
    error_str_t *err_p;

    for (err_p = errors; err_p->es_error != 0; err_p++) {
        if (err_p->es_error == error)
            return err_p->es_string;
    }

    return INVALID_ERROR;
}