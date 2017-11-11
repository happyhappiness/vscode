static void *merge_autoindex_configs(apr_pool_t *p, void *basev, void *addv)
{
    autoindex_config_rec *new;
    autoindex_config_rec *base = (autoindex_config_rec *) basev;
    autoindex_config_rec *add = (autoindex_config_rec *) addv;

    new = (autoindex_config_rec *) apr_pcalloc(p, sizeof(autoindex_config_rec));
    new->default_icon = add->default_icon ? add->default_icon
                                          : base->default_icon;
    new->style_sheet = add->style_sheet ? add->style_sheet
                                          : base->style_sheet;
    new->head_insert = add->head_insert ? add->head_insert
                                          : base->head_insert;
    new->header = add->header ? add->header
                                : base->header;
    new->readme = add->readme ? add->readme
                                : base->readme;
    new->icon_height = add->icon_height ? add->icon_height : base->icon_height;
    new->icon_width = add->icon_width ? add->icon_width : base->icon_width;

    new->ctype = add->ctype ? add->ctype : base->ctype;
    new->charset = add->charset ? add->charset : base->charset;

    new->alt_list = apr_array_append(p, add->alt_list, base->alt_list);
    new->desc_list = apr_array_append(p, add->desc_list, base->desc_list);
    new->icon_list = apr_array_append(p, add->icon_list, base->icon_list);
    new->ign_list = add->ign_noinherit ? add->ign_list : apr_array_append(p, add->ign_list, base->ign_list);
    if (add->opts == NO_OPTIONS) {
        /*
         * If the current directory explicitly says 'no options' then we also
         * clear any incremental mods from being inheritable further down.
         */
        new->opts = NO_OPTIONS;
        new->incremented_opts = 0;
        new->decremented_opts = 0;
    }
    else {
        /*
         * If there were any nonincremental options selected for
         * this directory, they dominate and we don't inherit *anything.*
         * Contrariwise, we *do* inherit if the only settings here are
         * incremental ones.
         */
        if (add->opts == OPTION_UNSET) {
            new->incremented_opts = (base->incremented_opts
                                     | add->incremented_opts)
                                    & ~add->decremented_opts;
            new->decremented_opts = (base->decremented_opts
                                     | add->decremented_opts);
            /*
             * We may have incremental settings, so make sure we don't
             * inadvertently inherit an IndexOptions None from above.
             */
            new->opts = (base->opts & ~NO_OPTIONS);
        }
        else {
            /*
             * There are local nonincremental settings, which clear
             * all inheritance from above.  They *are* the new base settings.
             */
            new->opts = add->opts;
        }
        /*
         * We're guaranteed that there'll be no overlap between
         * the add-options and the remove-options.
         */
        new->opts |= new->incremented_opts;
        new->opts &= ~new->decremented_opts;
    }
    /*
     * Inherit the NameWidth settings if there aren't any specific to
     * the new location; otherwise we'll end up using the defaults set in the
     * config-rec creation routine.
     */
    if (add->name_adjust == K_UNSET) {
        new->name_width = base->name_width;
        new->name_adjust = base->name_adjust;
    }
    else {
        new->name_width = add->name_width;
        new->name_adjust = add->name_adjust;
    }

    /*
     * Likewise for DescriptionWidth.
     */
    if (add->desc_adjust == K_UNSET) {
        new->desc_width = base->desc_width;
        new->desc_adjust = base->desc_adjust;
    }
    else {
        new->desc_width = add->desc_width;
        new->desc_adjust = add->desc_adjust;
    }

    new->default_keyid = add->default_keyid ? add->default_keyid
                                            : base->default_keyid;
    new->default_direction = add->default_direction ? add->default_direction
                                                    : base->default_direction;
    return new;
}