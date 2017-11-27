static int tcsv_config_add_instance_collect(instance_definition_t *id, oconfig_item_t *ci) {
    metric_definition_t *metric;
    metric_definition_t **metric_list;
    size_t metric_list_size;
    int i;

    if (ci->values_num < 1) {
        WARNING("tail_csv plugin: The `Collect' config option needs at least one argument.");
        return (-1);
    }

    metric_list_size = id->metric_list_len + (size_t) ci->values_num;
    metric_list = realloc (id->metric_list, sizeof (*id->metric_list) * metric_list_size);
    if (metric_list == NULL)
        return (-1);
    id->metric_list = metric_list;

    for (i = 0; i < ci->values_num; i++) {
        char *metric_name;

        if (ci->values[i].type != OCONFIG_TYPE_STRING) {
            WARNING("tail_csv plugin: All arguments to `Collect' must be strings.");
            continue;
        }
        metric_name = ci->values[i].value.string;

        for (metric = metric_head; metric != NULL; metric = metric->next)
            if (strcasecmp(metric_name, metric->name) == 0)
                break;

        if (metric == NULL) {
            WARNING ("tail_csv plugin: `Collect' argument not found `%s'.", metric_name);
            continue;
        }

        id->metric_list[id->metric_list_len] = metric;
        id->metric_list_len++;
    }

    return (0);
}