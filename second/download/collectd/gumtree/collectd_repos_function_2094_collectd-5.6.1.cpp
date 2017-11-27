static int wt_format_name(char *ret, int ret_len,
                          const value_list_t *vl,
                          const struct wt_callback *cb,
                          const char *ds_name)
{
    int status;
    char *temp = NULL;
    const char *prefix = "";
    const char *meta_prefix = "tsdb_prefix";

    if (vl->meta) {
        status = meta_data_get_string(vl->meta, meta_prefix, &temp);
        if (status == -ENOENT) {
            /* defaults to empty string */
        } else if (status < 0) {
            sfree(temp);
            return status;
        } else {
            prefix = temp;
        }
    }

    if (ds_name != NULL) {
        if (vl->plugin_instance[0] == '\0') {
            if (vl->type_instance[0] == '\0') {
                ssnprintf(ret, ret_len, "%s%s.%s.%s", prefix, vl->plugin,
                        vl->type, ds_name);
            } else {
                ssnprintf(ret, ret_len, "%s%s.%s.%s.%s", prefix, vl->plugin,
                        vl->type, vl->type_instance, ds_name);
            }
        } else { /* vl->plugin_instance != "" */
            if (vl->type_instance[0] == '\0') {
                ssnprintf(ret, ret_len, "%s%s.%s.%s.%s", prefix, vl->plugin,
                        vl->plugin_instance, vl->type, ds_name);
            } else {
                ssnprintf(ret, ret_len, "%s%s.%s.%s.%s.%s", prefix,
                        vl->plugin, vl->plugin_instance, vl->type,
                        vl->type_instance, ds_name);
            }
        }
    } else { /* ds_name == NULL */
        if (vl->plugin_instance[0] == '\0') {
            if (vl->type_instance[0] == '\0') {
                ssnprintf(ret, ret_len, "%s%s.%s", prefix, vl->plugin,
                        vl->type);
            } else {
                ssnprintf(ret, ret_len, "%s%s.%s.%s", prefix, vl->plugin,
                        vl->type_instance, vl->type);
            }
        } else { /* vl->plugin_instance != "" */
            if (vl->type_instance[0] == '\0') {
                ssnprintf(ret, ret_len, "%s%s.%s.%s", prefix, vl->plugin,
                        vl->plugin_instance, vl->type);
            } else {
                ssnprintf(ret, ret_len, "%s%s.%s.%s.%s", prefix, vl->plugin,
                        vl->plugin_instance, vl->type, vl->type_instance);
            }
        }
    }

    sfree(temp);
    return 0;
}