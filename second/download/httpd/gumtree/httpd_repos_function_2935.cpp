static void
argstr_to_table(char *str, apr_table_t *parms)
{
    char *key;
    char *value;
    char *strtok_state;

    if (str == NULL) {
        return;
    }
    
    key = apr_strtok(str, "&", &strtok_state);
    while (key) {
        value = strchr(key, '=');
        if (value) {
            *value = '\0';      /* Split the string in two */
            value++;            /* Skip passed the = */
        }
        else {
            value = "1";
        }
        ap_unescape_url(key);
        ap_unescape_url(value);
        apr_table_set(parms, key, value);
        key = apr_strtok(NULL, "&", &strtok_state);
    }
}