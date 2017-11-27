static void submit_value (int cpu_num, gauge_t percent)
{
    value_t values[1];
    value_list_t vl = VALUE_LIST_INIT;

    values[0].gauge = percent;

    vl.values = values;
    vl.values_len = 1;

    sstrncpy (vl.host, hostname_g, sizeof (vl.host));
    sstrncpy (vl.plugin, "xencpu", sizeof (vl.plugin));
    sstrncpy (vl.type, "percent", sizeof (vl.type));
    sstrncpy (vl.type_instance, "load", sizeof (vl.type_instance));

    if (cpu_num >= 0) {
        ssnprintf (vl.plugin_instance, sizeof (vl.plugin_instance),
                "%i", cpu_num);
    }
    plugin_dispatch_values (&vl);
}