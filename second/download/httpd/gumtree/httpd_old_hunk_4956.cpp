    /* remove ourselves */
    ap_remove_output_filter(f);
    return ap_pass_brigade(f->next, in);
}

/*
 * CACHE filter
 * ------------
 *
 * This filter can be optionally inserted into the filter chain by the admin as
 * a marker representing the precise location within the filter chain where
 * caching is to be performed.
