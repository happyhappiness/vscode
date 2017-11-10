static int get_max_ranges(request_rec *r) { 
    core_dir_config *core_conf = ap_get_module_config(r->per_dir_config, 
                                                      &core_module);
    if (core_conf->max_ranges >= 0 || core_conf->max_ranges == AP_MAXRANGES_UNLIMITED) { 
        return core_conf->max_ranges;
    }

    /* Any other negative val means the default */
    return AP_DEFAULT_MAX_RANGES;
}