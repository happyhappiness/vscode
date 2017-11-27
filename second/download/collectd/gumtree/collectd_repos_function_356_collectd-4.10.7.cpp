static void fscache_submit (const char *section, const char *name,
        counter_t counter_value)
{
    value_t values[1];
    value_list_t vl = VALUE_LIST_INIT;

    vl.values = values;
    vl.values_len = 1;

    vl.values[0].counter = counter_value;

    sstrncpy(vl.host, hostname_g, sizeof (vl.host));
    sstrncpy(vl.plugin, "fscache", sizeof (vl.plugin));
    sstrncpy(vl.plugin_instance, section, sizeof (vl.plugin_instance));
    sstrncpy(vl.type, "fscache_stat", sizeof(vl.type));
    sstrncpy(vl.type_instance, name, sizeof(vl.type_instance));

    plugin_dispatch_values (&vl);
}