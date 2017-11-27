static void report_lv_utilization(lv_t lv, char const *vg_name,
        char const *lv_name, uint64_t lv_size,
        char const *used_percent_property)
{
    uint64_t used_percent_unscaled;
    uint64_t used_bytes;
    char plugin_instance[DATA_MAX_NAME_LEN];

    used_percent_unscaled = get_lv_property_int(lv, used_percent_property);
    if (used_percent_unscaled == NO_VALUE)
        return;
    used_bytes = lv_size * (used_percent_unscaled * PERCENT_SCALE_FACTOR);

    ssnprintf(plugin_instance, sizeof(plugin_instance), "%s-%s",
            vg_name, lv_name);
    lvm_submit(plugin_instance, "used", used_bytes);
    lvm_submit(plugin_instance, "free", lv_size - used_bytes);
}