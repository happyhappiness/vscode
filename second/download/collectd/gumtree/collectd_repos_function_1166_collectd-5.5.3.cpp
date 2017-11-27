static _Bool tcsv_check_index (int index, size_t fields_num, char const *name)
{
    if (index < 0)
        return 1;
    else if (((size_t) index) < fields_num)
        return 1;

    ERROR ("tail_csv plugin: Metric \"%s\": Request for index %i when "
            "only %zu fields are available.",
            name, index, fields_num);
    return (0);
}