static const char 
*set_max_cache_size(cmd_parms *parms, void *in_struct_ptr, const char *arg)
{
    apr_size_t val;

    if (sscanf(arg, "%" APR_SIZE_T_FMT, &val) != 1) {
        return "MCacheSize argument must be an integer representing the max cache size in KBytes.";
    }
    sconf->max_cache_size = val*1024;
    return NULL;
}