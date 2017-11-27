static char const *get_lv_property_string(lv_t lv, char const *property)
{
    lvm_property_value_t v;

    v = lvm_lv_get_property(lv, property);
    if (!v.is_valid || !v.is_string)
        return NULL;
    return v.value.string;
}