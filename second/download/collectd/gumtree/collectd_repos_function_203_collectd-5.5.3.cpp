static int gr_format_name (char *ret, int ret_len,
        value_list_t const *vl,
        char const *ds_name,
        char const *prefix,
        char const *postfix,
        char const escape_char,
        unsigned int flags)
{
    char n_host[DATA_MAX_NAME_LEN];
    char n_plugin[DATA_MAX_NAME_LEN];
    char n_plugin_instance[DATA_MAX_NAME_LEN];
    char n_type[DATA_MAX_NAME_LEN];
    char n_type_instance[DATA_MAX_NAME_LEN];

    char tmp_plugin[2 * DATA_MAX_NAME_LEN + 1];
    char tmp_type[2 * DATA_MAX_NAME_LEN + 1];

    if (prefix == NULL)
        prefix = "";

    if (postfix == NULL)
        postfix = "";

    gr_copy_escape_part (n_host, vl->host,
            sizeof (n_host), escape_char);
    gr_copy_escape_part (n_plugin, vl->plugin,
            sizeof (n_plugin), escape_char);
    gr_copy_escape_part (n_plugin_instance, vl->plugin_instance,
            sizeof (n_plugin_instance), escape_char);
    gr_copy_escape_part (n_type, vl->type,
            sizeof (n_type), escape_char);
    gr_copy_escape_part (n_type_instance, vl->type_instance,
            sizeof (n_type_instance), escape_char);

    if (n_plugin_instance[0] != '\0')
        ssnprintf (tmp_plugin, sizeof (tmp_plugin), "%s%c%s",
            n_plugin,
            (flags & GRAPHITE_SEPARATE_INSTANCES) ? '.' : '-',
            n_plugin_instance);
    else
        sstrncpy (tmp_plugin, n_plugin, sizeof (tmp_plugin));

    if (n_type_instance[0] != '\0')
        ssnprintf (tmp_type, sizeof (tmp_type), "%s%c%s",
            n_type,
            (flags & GRAPHITE_SEPARATE_INSTANCES) ? '.' : '-',
            n_type_instance);
    else
        sstrncpy (tmp_type, n_type, sizeof (tmp_type));

    /* Assert always_append_ds -> ds_name */
    assert (!(flags & GRAPHITE_ALWAYS_APPEND_DS) || (ds_name != NULL));
    if (ds_name != NULL)
        ssnprintf (ret, ret_len, "%s%s%s.%s.%s.%s",
            prefix, n_host, postfix, tmp_plugin, tmp_type, ds_name);
    else
        ssnprintf (ret, ret_len, "%s%s%s.%s.%s",
            prefix, n_host, postfix, tmp_plugin, tmp_type);

    return (0);
}