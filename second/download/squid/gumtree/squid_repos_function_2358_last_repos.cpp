inline
const char *
errorTypeName(err_type err)
{
    if (err < ERR_NONE || err >= ERR_MAX)
        return "UNKNOWN";
    return err_type_str[err];
}