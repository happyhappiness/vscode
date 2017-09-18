
    return APR_SUCCESS;
}

static void register_hooks(apr_pool_t *p)
{
    ap_register_output_filter(deflateFilterName, deflate_out_filter, NULL,
                              AP_FTYPE_CONTENT_SET);
    ap_register_input_filter(deflateFilterName, deflate_in_filter, NULL,
                              AP_FTYPE_CONTENT_SET);
}

static const command_rec deflate_filter_cmds[] = {
    AP_INIT_TAKE1("DeflateFilterNote", deflate_set_note, NULL, RSRC_CONF,
                  "Set a note to report on compression ratio"),
