static void *overlay_hook_specs(apr_pool_t *p,
                                        const void *key,
                                        apr_ssize_t klen,
                                        const void *overlay_val,
                                        const void *base_val,
                                        const void *data)
{
    const apr_array_header_t *overlay_info = (const apr_array_header_t*)overlay_val;
    const apr_array_header_t *base_info = (const apr_array_header_t*)base_val;
    return apr_array_append(p, base_info, overlay_info);
}