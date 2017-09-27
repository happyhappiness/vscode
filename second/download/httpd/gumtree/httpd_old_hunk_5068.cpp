    spec->filter_name = filter;

    *(ap_lua_filter_handler_spec **) apr_array_push(cfg->mapped_filters) = spec;
    /* TODO: Make it work on other types than just AP_FTYPE_RESOURCE? */
    if (direction == AP_LUA_FILTER_OUTPUT) {
        spec->direction = AP_LUA_FILTER_OUTPUT;
        ap_register_output_filter(filter, lua_output_filter_handle, NULL, AP_FTYPE_RESOURCE);
    }
    else {
        spec->direction = AP_LUA_FILTER_INPUT;
        ap_register_input_filter(filter, lua_input_filter_handle, NULL, AP_FTYPE_RESOURCE);
    }
    return NULL;
