static int tcsv_config_get_index(oconfig_item_t *ci, int *ret_index) {
    int index;

    if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_NUMBER)){
        WARNING("tail_csv plugin: The \"%s\" config option needs exactly one "
                "integer argument.", ci->key);
        return (-1);
    }

    index = (int) ci->values[0].value.number;
    if (index < 0) {
        WARNING("tail_csv plugin: The \"%s\" config option must be positive "
                "(or zero).", ci->key);
        return (-1);
    }

    *ret_index = index;
    return (0);
}