static int tcsv_init(void) { /* {{{ */
    static _Bool have_init = 0;
    metric_definition_t *md;

    if (have_init)
        return (0);

    for (md = metric_head; md != NULL; md = md->next) {
        data_set_t const *ds;

        /* Retrieve the data source type from the types db. */
        ds = plugin_get_ds(md->type);
        if (ds == NULL)
        {
            ERROR ("tail_csv plugin: Failed to look up type \"%s\" for "
                    "metric \"%s\". It may not be defined in the types.db "
                    "file. Please read the types.db(5) manual page for more "
                    "details.",
                    md->type, md->name);
            continue;
        }
        else if (ds->ds_num != 1)
        {
            ERROR ("tail_csv plugin: The type \"%s\" has %zu data sources. "
                    "Only types with a single data soure are supported.",
                    ds->type, ds->ds_num);
            continue;
        }

        md->data_source_type = ds->ds->type;
    }

    return (0);
}