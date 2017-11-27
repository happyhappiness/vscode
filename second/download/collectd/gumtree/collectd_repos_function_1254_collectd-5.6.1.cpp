static int tcsv_config(oconfig_item_t *ci){
    for (int i = 0; i < ci->children_num; ++i){
        oconfig_item_t *child = ci->children + i;
        if (strcasecmp("Metric", child->key) == 0)
            tcsv_config_add_metric(child);
        else if (strcasecmp("File", child->key) == 0)
            tcsv_config_add_file(child);
        else
            WARNING("tail_csv plugin: Ignore unknown config option `%s'.", child->key);
    }

    return (0);
}