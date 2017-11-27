static void
vcpu_submit (derive_t cpu_time,
             virDomainPtr dom, int vcpu_nr, const char *type)
{
    value_t values[1];
    value_list_t vl = VALUE_LIST_INIT;

    init_value_list (&vl, dom);

    values[0].derive = cpu_time;
    vl.values = values;
    vl.values_len = 1;

    sstrncpy (vl.type, type, sizeof (vl.type));
    ssnprintf (vl.type_instance, sizeof (vl.type_instance), "%d", vcpu_nr);

    plugin_dispatch_values (&vl);
}