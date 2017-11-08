static const char *log_remote_user(request_rec *r, char *a)
{
    char *rvalue = r->user;

    if (rvalue == NULL) {
        rvalue = "-";
    }
    else if (strlen(rvalue) == 0) {
        rvalue = "\"\"";
    }
    return rvalue;
}