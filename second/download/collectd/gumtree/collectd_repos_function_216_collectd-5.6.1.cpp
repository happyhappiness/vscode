static void
memory_submit (gauge_t memory, virDomainPtr dom)
{
    value_t values[1];
    value_list_t vl = VALUE_LIST_INIT;

    init_value_list (&vl, dom);

    values[0].gauge = memory;

    vl.values = values;
    vl.values_len = 1;

    sstrncpy (vl.type, "memory", sizeof (vl.type));
    sstrncpy (vl.type_instance, "total", sizeof (vl.type_instance));

    plugin_dispatch_values (&vl);
}