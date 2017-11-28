static int copy_cn(void *check_data,  ASN1_STRING *cn_data)
{
    String *str = (String *)check_data;
    if (!str) // no data? abort
        return 0;
    if (cn_data && cn_data->length) {
        if (str->size() > 0)
            str->append(", ");
        str->append((const char *)cn_data->data, cn_data->length);
    }
    return 1;
}