static void validate_status_line(request_rec *r)
{
    char *end;

    if (r->status_line
        && (strlen(r->status_line) <= 4
            || apr_strtoi64(r->status_line, &end, 10) != r->status
            || *end != ' '
            || (end - 3) != r->status_line)) {
        r->status_line = NULL;
    }
}