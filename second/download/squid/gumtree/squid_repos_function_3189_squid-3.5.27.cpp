const char *KRB5_CALLCONV error_message(long code) {
    char *msg = NULL;
    krb5_svc_get_msg(code, &msg);
    return msg;
}