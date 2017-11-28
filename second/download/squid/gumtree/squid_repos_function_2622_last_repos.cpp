const char *KRB5_CALLCONV
error_message(long code) {
    snprintf(err_code,16,"%ld",code);
    return err_code;
}