static void *overlay_extension_mappings(apr_pool_t *p,
                                        const void *key,
                                        apr_ssize_t klen,
                                        const void *overlay_val,
                                        const void *base_val,
                                        const void *data)
{
    const extension_info *overlay_info = (const extension_info *)overlay_val;
    const extension_info *base_info = (const extension_info *)base_val;
    extension_info *new_info = apr_pmemdup(p, base_info, sizeof(extension_info));

    if (overlay_info->forced_type) {
        new_info->forced_type = overlay_info->forced_type;
    }
    if (overlay_info->encoding_type) {
        new_info->encoding_type = overlay_info->encoding_type;
    }
    if (overlay_info->language_type) {
        new_info->language_type = overlay_info->language_type;
    }
    if (overlay_info->handler) {
        new_info->handler = overlay_info->handler;
    }
    if (overlay_info->charset_type) {
        new_info->charset_type = overlay_info->charset_type;
    }
    if (overlay_info->input_filters) {
        new_info->input_filters = overlay_info->input_filters;
    }
    if (overlay_info->output_filters) {
        new_info->output_filters = overlay_info->output_filters;
    }

    return new_info;
}