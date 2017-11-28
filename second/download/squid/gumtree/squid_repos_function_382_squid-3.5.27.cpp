static void
k5_error2(const char* msg, char* msg2, krb5_error_code code)
{
    const char *errmsg;
    errmsg = krb5_get_error_message(kparam.context, code);
    error((char *) "%s| %s: ERROR: %s%s : %s\n", LogTime(), PROGRAM, msg, msg2, errmsg);
#if HAVE_KRB5_FREE_ERROR_MESSAGE
    krb5_free_error_message(kparam.context, errmsg);
#elif HAVE_KRB5_FREE_ERROR_STRING
    krb5_free_error_string(kparam.context, (char *)errmsg);
#else
    xfree(errmsg);
#endif
}