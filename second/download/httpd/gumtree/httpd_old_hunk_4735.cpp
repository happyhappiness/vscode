    }

    apr_brigade_cleanup(bb);
    return APR_SUCCESS;
}

#define PROTO_FLAGS AP_FILTER_PROTO_CHANGE|AP_FILTER_PROTO_CHANGE_LENGTH
static void register_hooks(apr_pool_t *p)
{
    ap_register_output_filter(deflateFilterName, deflate_out_filter, NULL,
                              AP_FTYPE_CONTENT_SET);
    ap_register_output_filter("INFLATE", inflate_out_filter, NULL,
                              AP_FTYPE_RESOURCE-1);
    ap_register_input_filter(deflateFilterName, deflate_in_filter, NULL,
                              AP_FTYPE_CONTENT_SET);
}

static const command_rec deflate_filter_cmds[] = {
    AP_INIT_TAKE12("DeflateFilterNote", deflate_set_note, NULL, RSRC_CONF,
                  "Set a note to report on compression ratio"),
    AP_INIT_TAKE1("DeflateWindowSize", deflate_set_window_size, NULL,
