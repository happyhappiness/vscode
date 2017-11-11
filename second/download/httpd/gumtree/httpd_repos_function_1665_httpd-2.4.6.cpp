static const char *add_opts(cmd_parms *cmd, void *d, int argc, char *const argv[])
{
    int i;
    char *w;
    apr_int32_t opts;
    apr_int32_t opts_add;
    apr_int32_t opts_remove;
    char action;
    autoindex_config_rec *d_cfg = (autoindex_config_rec *) d;

    opts = d_cfg->opts;
    opts_add = d_cfg->incremented_opts;
    opts_remove = d_cfg->decremented_opts;

    for (i = 0; i < argc; i++) {
        int option = 0;
        w = argv[i];

        if ((*w == '+') || (*w == '-')) {
            action = *(w++);
        }
        else {
            action = '\0';
        }
        if (!strcasecmp(w, "FancyIndexing")) {
            option = FANCY_INDEXING;
        }
        else if (!strcasecmp(w, "FoldersFirst")) {
            option = FOLDERS_FIRST;
        }
        else if (!strcasecmp(w, "HTMLTable")) {
            option = TABLE_INDEXING;
        }
        else if (!strcasecmp(w, "IconsAreLinks")) {
            option = ICONS_ARE_LINKS;
        }
        else if (!strcasecmp(w, "IgnoreCase")) {
            option = IGNORE_CASE;
        }
        else if (!strcasecmp(w, "IgnoreClient")) {
            option = IGNORE_CLIENT;
        }
        else if (!strcasecmp(w, "ScanHTMLTitles")) {
            option = SCAN_HTML_TITLES;
        }
        else if (!strcasecmp(w, "SuppressColumnSorting")) {
            option = SUPPRESS_COLSORT;
        }
        else if (!strcasecmp(w, "SuppressDescription")) {
            option = SUPPRESS_DESC;
        }
        else if (!strcasecmp(w, "SuppressHTMLPreamble")) {
            option = SUPPRESS_PREAMBLE;
        }
        else if (!strcasecmp(w, "SuppressIcon")) {
            option = SUPPRESS_ICON;
        }
        else if (!strcasecmp(w, "SuppressLastModified")) {
            option = SUPPRESS_LAST_MOD;
        }
        else if (!strcasecmp(w, "SuppressSize")) {
            option = SUPPRESS_SIZE;
        }
        else if (!strcasecmp(w, "SuppressRules")) {
            option = SUPPRESS_RULES;
        }
        else if (!strcasecmp(w, "TrackModified")) {
            option = TRACK_MODIFIED;
        }
        else if (!strcasecmp(w, "VersionSort")) {
            option = VERSION_SORT;
        }
        else if (!strcasecmp(w, "XHTML")) {
            option = EMIT_XHTML;
        }
        else if (!strcasecmp(w, "ShowForbidden")) {
            option = SHOW_FORBIDDEN;
        }
        else if (!strcasecmp(w, "AddAltClass")) {
            option = ADDALTCLASS;
        }
        else if (!strcasecmp(w, "None")) {
            if (action != '\0') {
                return "Cannot combine '+' or '-' with 'None' keyword";
            }
            opts = NO_OPTIONS;
            opts_add = 0;
            opts_remove = 0;
        }
        else if (!strcasecmp(w, "IconWidth")) {
            if (action != '-') {
                d_cfg->icon_width = DEFAULT_ICON_WIDTH;
            }
            else {
                d_cfg->icon_width = 0;
            }
        }
        else if (!strncasecmp(w, "IconWidth=", 10)) {
            if (action == '-') {
                return "Cannot combine '-' with IconWidth=n";
            }
            d_cfg->icon_width = atoi(&w[10]);
        }
        else if (!strcasecmp(w, "IconHeight")) {
            if (action != '-') {
                d_cfg->icon_height = DEFAULT_ICON_HEIGHT;
            }
            else {
                d_cfg->icon_height = 0;
            }
        }
        else if (!strncasecmp(w, "IconHeight=", 11)) {
            if (action == '-') {
                return "Cannot combine '-' with IconHeight=n";
            }
            d_cfg->icon_height = atoi(&w[11]);
        }
        else if (!strcasecmp(w, "NameWidth")) {
            if (action != '-') {
                return "NameWidth with no value may only appear as "
                       "'-NameWidth'";
            }
            d_cfg->name_width = DEFAULT_NAME_WIDTH;
            d_cfg->name_adjust = K_NOADJUST;
        }
        else if (!strncasecmp(w, "NameWidth=", 10)) {
            if (action == '-') {
                return "Cannot combine '-' with NameWidth=n";
            }
            if (w[10] == '*') {
                d_cfg->name_adjust = K_ADJUST;
            }
            else {
                int width = atoi(&w[10]);

                if (width && (width < 5)) {
                    return "NameWidth value must be greater than 5";
                }
                d_cfg->name_width = width;
                d_cfg->name_adjust = K_NOADJUST;
            }
        }
        else if (!strcasecmp(w, "DescriptionWidth")) {
            if (action != '-') {
                return "DescriptionWidth with no value may only appear as "
                       "'-DescriptionWidth'";
            }
            d_cfg->desc_width = DEFAULT_DESC_WIDTH;
            d_cfg->desc_adjust = K_NOADJUST;
        }
        else if (!strncasecmp(w, "DescriptionWidth=", 17)) {
            if (action == '-') {
                return "Cannot combine '-' with DescriptionWidth=n";
            }
            if (w[17] == '*') {
                d_cfg->desc_adjust = K_ADJUST;
            }
            else {
                int width = atoi(&w[17]);

                if (width && (width < 12)) {
                    return "DescriptionWidth value must be greater than 12";
                }
                d_cfg->desc_width = width;
                d_cfg->desc_adjust = K_NOADJUST;
            }
        }
        else if (!strncasecmp(w, "Type=", 5)) {
            d_cfg->ctype = apr_pstrdup(cmd->pool, &w[5]);
        }
        else if (!strncasecmp(w, "Charset=", 8)) {
            d_cfg->charset = apr_pstrdup(cmd->pool, &w[8]);
        }
        else {
            return "Invalid directory indexing option";
        }
        if (action == '\0') {
            opts |= option;
            opts_add = 0;
            opts_remove = 0;
        }
        else if (action == '+') {
            opts_add |= option;
            opts_remove &= ~option;
        }
        else {
            opts_remove |= option;
            opts_add &= ~option;
        }
    }
    if ((opts & NO_OPTIONS) && (opts & ~NO_OPTIONS)) {
        return "Cannot combine other IndexOptions keywords with 'None'";
    }
    d_cfg->incremented_opts = opts_add;
    d_cfg->decremented_opts = opts_remove;
    d_cfg->opts = opts;
    return NULL;
}