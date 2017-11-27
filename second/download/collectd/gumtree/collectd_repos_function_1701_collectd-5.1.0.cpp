static int wg_format_name (char *ret, int ret_len,
        const value_list_t *vl,
        const struct wg_callback *cb,
        const char *ds_name)
{
    char n_host[DATA_MAX_NAME_LEN];
    char n_plugin[DATA_MAX_NAME_LEN];
    char n_plugin_instance[DATA_MAX_NAME_LEN];
    char n_type[DATA_MAX_NAME_LEN];
    char n_type_instance[DATA_MAX_NAME_LEN];

    char *prefix;
    char *postfix;

    char tmp_plugin[2 * DATA_MAX_NAME_LEN + 1];
    char tmp_type[2 * DATA_MAX_NAME_LEN + 1];

    prefix = cb->prefix;
    if (prefix == NULL)
        prefix = "";

    postfix = cb->postfix;
    if (postfix == NULL)
        postfix = "";

    wg_copy_escape_part (n_host, vl->host,
            sizeof (n_host), cb->escape_char);
    wg_copy_escape_part (n_plugin, vl->plugin,
            sizeof (n_plugin), cb->escape_char);
    wg_copy_escape_part (n_plugin_instance, vl->plugin_instance,
            sizeof (n_plugin_instance), cb->escape_char);
    wg_copy_escape_part (n_type, vl->type,
            sizeof (n_type), cb->escape_char);
    wg_copy_escape_part (n_type_instance, vl->type_instance,
            sizeof (n_type_instance), cb->escape_char);

    if (n_plugin_instance[0] != '\0')
        ssnprintf (tmp_plugin, sizeof (tmp_plugin), "%s%c%s",
            n_plugin,
            cb->separate_instances ? '.' : '-',
            n_plugin_instance);
    else
        sstrncpy (tmp_plugin, n_plugin, sizeof (tmp_plugin));

    if (n_type_instance[0] != '\0')
        ssnprintf (tmp_type, sizeof (tmp_type), "%s%c%s",
            n_type,
            cb->separate_instances ? '.' : '-',
            n_type_instance);
    else
        sstrncpy (tmp_type, n_type, sizeof (tmp_type));

    if (ds_name != NULL)
        ssnprintf (ret, ret_len, "%s%s%s.%s.%s.%s",
            prefix, n_host, postfix, tmp_plugin, tmp_type, ds_name);
    else
        ssnprintf (ret, ret_len, "%s%s%s.%s.%s",
            prefix, n_host, postfix, tmp_plugin, tmp_type);

    return (0);
}