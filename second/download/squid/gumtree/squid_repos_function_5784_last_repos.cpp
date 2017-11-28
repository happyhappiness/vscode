int
check_k5_err(krb5_context context, const char *function, krb5_error_code code)
{

    if (code && code != KRB5_KT_END) {
        const char *errmsg;
        errmsg = krb5_get_error_message(context, code);
        debug((char *) "%s| %s: ERROR: %s failed: %s\n", LogTime(), PROGRAM, function, errmsg);
        fprintf(stderr, "%s| %s: ERROR: %s: %s\n", LogTime(), PROGRAM, function, errmsg);
#if HAVE_KRB5_FREE_ERROR_MESSAGE
        krb5_free_error_message(context, errmsg);
#elif HAVE_KRB5_FREE_ERROR_STRING
        krb5_free_error_string(context, (char *)errmsg);
#else
        xfree(errmsg);
#endif
    }
    return code;
}