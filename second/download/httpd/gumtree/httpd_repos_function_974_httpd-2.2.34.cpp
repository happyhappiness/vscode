static const char
*set_max_cache_object_size(cmd_parms *parms, void *in_struct_ptr, const char *arg)
{
    apr_size_t val;

    if (sscanf(arg, "%" APR_SIZE_T_FMT, &val) != 1) {
        return "MCacheMaxObjectSize value must be an integer (bytes)";
    }
    sconf->max_cache_object_size = val;
    return NULL;
}