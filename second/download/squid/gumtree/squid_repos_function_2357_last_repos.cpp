inline
err_type
errorTypeByName(const char *name)
{
    for (int i = 0; i < ERR_MAX; ++i)
        if (strcmp(name, err_type_str[i]) == 0)
            return (err_type)i;
    return ERR_MAX;
}