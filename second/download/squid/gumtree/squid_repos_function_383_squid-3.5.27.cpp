static void
k5_error(const char* msg, krb5_error_code code)
{
    k5_error2(msg, (char *)"", code);
}