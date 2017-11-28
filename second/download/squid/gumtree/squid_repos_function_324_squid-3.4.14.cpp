int
check_k5_err(krb5_context context, const char *function, krb5_error_code code)
{
    const char *errmsg;

    if (code) {
        errmsg = krb5_get_error_message(context, code);
        debug((char *) "%s| %s: ERROR: %s failed: %s\n", LogTime(), PROGRAM, function, errmsg);
        fprintf(stderr, "%s| %s: ERROR: %s: %s\n", LogTime(), PROGRAM, function, errmsg);
        krb5_free_error_message(context, errmsg);
    }
    return code;
}