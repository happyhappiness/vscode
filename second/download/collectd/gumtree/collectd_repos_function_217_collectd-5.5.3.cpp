static void
memory_stats_submit (gauge_t memory, virDomainPtr dom, int tag_index)
{
    static const char *tags[] = { "swap_in", "swap_out", "major_fault", "minor_fault",
                                    "unused", "available", "actual_balloon", "rss"};

    value_t values[1];
    value_list_t vl = VALUE_LIST_INIT;

    init_value_list (&vl, dom);

    values[0].gauge = memory;

    vl.values = values;
    vl.values_len = 1;

    sstrncpy (vl.type, "memory", sizeof (vl.type));
    sstrncpy (vl.type_instance, tags[tag_index], sizeof (vl.type_instance));

    plugin_dispatch_values (&vl);
}