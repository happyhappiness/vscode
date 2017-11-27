static void
submit_counter2 (const char *type, counter_t v0, counter_t v1,
             time_t t,
             virDomainPtr dom, const char *devname)
{
    value_t values[2];
    value_list_t vl = VALUE_LIST_INIT;

    init_value_list (&vl, t, dom);

    values[0].counter = v0;
    values[1].counter = v1;
    vl.values = values;
    vl.values_len = 2;

    sstrncpy (vl.type, type, sizeof (vl.type));
    sstrncpy (vl.type_instance, devname, sizeof (vl.type_instance));

    plugin_dispatch_values (&vl);
}