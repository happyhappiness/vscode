static const char *add_opts(cmd_parms *cmd, void *d, const char *optstr)
{
    char *w;
    apr_int32_t opts;
    apr_int32_t opts_add;
    apr_int32_t opts_remove;
    char action;
    autoindex_config_rec *d_cfg = (autoindex_config_rec *) d;

    opts = d_cfg->opts;
    opts_add = d_cfg->incremented_opts;
    opts_remove = d_cfg->decremented_opts;
    while (optstr[0]) {
        int option = 0;

        w = ap_getword_conf(cmd->pool, &optstr);
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
                d_cfg->name_adjust