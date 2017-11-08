static int mod_fcgid_modify_auth_header(void *vars,
                                        const char *key, const char *val)
{
    /* When the application gives a 200 response, the server ignores response
       headers whose names aren't prefixed with Variable- prefix, and ignores
       any response content */
    if (strncasecmp(key, "Variable-", 9) == 0)
        apr_table_setn(vars, key, val);
    return 1;
}