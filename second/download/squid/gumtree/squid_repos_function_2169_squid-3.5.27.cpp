cbdata_type
cbdataInternalAddType(cbdata_type type, const char *name, int size, FREE * free_func)
{
    if (type)
        return type;

    type = (cbdata_type)(cbdata_types + 1);

    cbdataInternalInitType(type, name, size, free_func);

    return type;
}