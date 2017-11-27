static void
cpu_submit (unsigned long long cpu_time,
            time_t t,
            virDomainPtr dom, const char *type)
{
    value_t values[1];
    value_list_t vl = VALUE_LIST_INIT;

    init_value_list (&vl, t, dom);

    values[0].counter = cpu_time;

    vl.values = values;
    vl.values_len = 1;

    sstrncpy (vl.type, type, sizeof (vl.type));

    plugin_dispatch_values (&vl);
}