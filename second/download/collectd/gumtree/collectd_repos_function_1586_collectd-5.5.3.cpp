static uint64_t get_lv_property_int(lv_t lv, char const *property)
{
    lvm_property_value_t v;

    v = lvm_lv_get_property(lv, property);
    if (!v.is_valid || !v.is_integer)
        return NO_VALUE;
    /* May be NO_VALUE if @property does not apply to this LV */
    return v.value.integer;
}