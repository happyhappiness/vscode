static authz_status all_check_authorization(request_rec *r, const char *require_line)
{
    /* If the argument to the 'all' provider is 'granted' then just let 
        everybody in. This would be equivalent to the previous syntax of
        'allow from all'. If the argument is anything else, this would
        be equivalent to 'deny from all' Of course the opposite would be 
        true if the 'all' provider is invoked by the 'reject' directive */
    if (strcasecmp(require_line, "granted") == 0) {
        return AUTHZ_GRANTED;
    }
    return AUTHZ_DENIED;
}