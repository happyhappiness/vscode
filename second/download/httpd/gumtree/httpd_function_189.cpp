static void output_directories(struct ent **ar, int n,
                               autoindex_config_rec *d, request_rec *r,
                               apr_int32_t autoindex_opts, char keyid, 
                               char direction, const char *colargs)
{
    int x;
    apr_size_t rv;
    char *name = r->uri;
    char *tp;
    int static_columns = !!(autoindex_opts & SUPPRESS_COLSORT);
    apr_pool_t *scratch;
    int name_width;
    int desc_width;
    char *name_scratch;
    char *pad_scratch;
    char *breakrow = "";

    apr_pool_create(&scratch, r->pool);
    if (name[0] == '\0') {
        name = "/";
    }

    name_width = d->name_width;
    desc_width = d->desc_width; 

    if ((autoindex_opts & (FANCY_INDEXING | TABLE_INDEXING)) 
                        == FANCY_INDEXING) {
        if (d->name_adjust == K_ADJUST) {
            for (x = 0; x < n; x++) {
                int t = strlen(ar[x]->name);
                if (t > name_width) {
                    name_width = t;
                }
            }
        }

        if (d->desc_adjust == K_ADJUST) { 
            for (x = 0; x < n; x++) {
                if (ar[x]->desc != NULL) { 
                    int t = strlen(ar[x]->desc); 
                    if (t > desc_width) { 
                        desc_width = t; 
                    } 
                } 
            } 
        } 
    }
    name_scratch = apr_palloc(r->pool, name_width + 1);
    pad_scratch = apr_palloc(r->pool, name_width + 1);
    memset(pad_scratch, ' ', name_width);
    pad_scratch[name_width] = '\0';

    if (autoindex_opts & TABLE_INDEXING) {
        int cols = 1;
        ap_rputs("<table><tr>", r);
        if (!(autoindex_opts & SUPPRESS_ICON)) {
            ap_rputs("<th>", r);
            if ((tp = find_default_icon(d, "^^BLANKICON^^"))) {
                ap_rvputs(r, "<img src=\"", ap_escape_html(scratch, tp),
                             "\" alt=\"[ICO]\"", NULL);
                if (d->icon_width) {
                    ap_rprintf(r, " width=\"%d\"", d->icon_width);
                }
                if (d->icon_height) {
                    ap_rprintf(r, " height=\"%d\"", d->icon_height);
                }
                ap_rputs(" /></th>", r);
            }
            else {
                ap_rputs("&nbsp;</th>", r);
            }
            
            ++cols;
        }
        ap_rputs("<th>", r);
        emit_link(r, "Name", K_NAME, keyid, direction, 
                  colargs, static_columns);
        if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
            ap_rputs("</th><th>", r);
            emit_link(r, "Last modified", K_LAST_MOD, keyid, direction, 
                      colargs, static_columns);
            ++cols;
        }
        if (!(autoindex_opts & SUPPRESS_SIZE)) {
            ap_rputs("</th><th>", r);
            emit_link(r, "Size", K_SIZE, keyid, direction, 
                      colargs, static_columns);
            ++cols;
        }
        if (!(autoindex_opts & SUPPRESS_DESC)) {
            ap_rputs("</th><th>", r);
            emit_link(r, "Description", K_DESC, keyid, direction, 
                      colargs, static_columns);
            ++cols;
        }
        if (!(autoindex_opts & SUPPRESS_RULES)) {
            breakrow = apr_psprintf(r->pool,
                                    "<tr><th colspan=\"%d\">"
                                    "<hr /></th></tr>\n", cols);
        }
        ap_rvputs(r, "</th></tr>", breakrow, NULL);
    }
    else if (autoindex_opts & FANCY_INDEXING) {
        ap_rputs("<pre>", r);
        if (!(autoindex_opts & SUPPRESS_ICON)) {
            if ((tp = find_default_icon(d, "^^BLANKICON^^"))) {
                ap_rvputs(r, "<img src=\"", ap_escape_html(scratch, tp),
                             "\" alt=\"Icon \"", NULL);
                if (d->icon_width) {
                    ap_rprintf(r, " width=\"%d\"", d->icon_width);
                }
                if (d->icon_height) {
                    ap_rprintf(r, " height=\"%d\"", d->icon_height);
                }
                ap_rputs(" /> ", r);
            }
            else {
                ap_rputs("      ", r);
            }
        }
        emit_link(r, "Name", K_NAME, keyid, direction, 
                  colargs, static_columns);
        ap_rputs(pad_scratch + 4, r);
        /*
         * Emit the guaranteed-at-least-one-space-between-columns byte.
         */
        ap_rputs(" ", r);
        if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
            emit_link(r, "Last modified", K_LAST_MOD, keyid, direction,
                      colargs, static_columns);
            ap_rputs("      ", r);
        }
        if (!(autoindex_opts & SUPPRESS_SIZE)) {
            emit_link(r, "Size", K_SIZE, keyid, direction, 
                      colargs, static_columns);
            ap_rputs("  ", r);
        }
        if (!(autoindex_opts & SUPPRESS_DESC)) {
            emit_link(r, "Description", K_DESC, keyid, direction,
                      colargs, static_columns);
        }
        if (!(autoindex_opts & SUPPRESS_RULES)) {
            ap_rputs("<hr />", r);
        }
        else {
            ap_rputc('\n', r);
        }
    }
    else {
        ap_rputs("<ul>", r);
    }

    for (x = 0; x < n; x++) {
        char *anchor, *t, *t2;
        int nwidth;

        apr_pool_clear(scratch);

        t = ar[x]->name;
        anchor = ap_escape_html(scratch, ap_os_escape_path(scratch, t, 0));

        if (!x && t[0] == '/') {
            t2 = "Parent Directory";
        }
        else {
            t2 = t;
        }

        if (autoindex_opts & TABLE_INDEXING) {
            if (!(autoindex_opts & SUPPRESS_ICON)) {
                ap_rputs("<tr><td valign=\"top\">", r);
                if (autoindex_opts & ICONS_ARE_LINKS) {
                    ap_rvputs(r, "<a href=\"", anchor, "\">", NULL);
                }
                if ((ar[x]->icon) || d->default_icon) {
                    ap_rvputs(r, "<img src=\"",
                              ap_escape_html(scratch,
                                             ar[x]->icon ? ar[x]->icon
                                                         : d->default_icon),
                              "\" alt=\"[", (ar[x]->alt ? ar[x]->alt : "   "),
                              "]\"", NULL);
                    if (d->icon_width) {
                        ap_rprintf(r, " width=\"%d\"", d->icon_width);
                    }
                    if (d->icon_height) {
                        ap_rprintf(r, " height=\"%d\"", d->icon_height);
                    }
                    ap_rputs(" />", r);
                }
                else {
                    ap_rputs("&nbsp;", r);            
                }
                if (autoindex_opts & ICONS_ARE_LINKS) {
                    ap_rputs("</a></td>", r);
                }
                else {
                    ap_rputs("</td>", r);
                }
            }
            if (d->name_adjust == K_ADJUST) {
                ap_rvputs(r, "<td><a href=\"", anchor, "\">",
                          ap_escape_html(scratch, t2), "</a>", NULL);
            }
            else {
                nwidth = strlen(t2);
                if (nwidth > name_width) {
                  memcpy(name_scratch, t2, name_width - 3);
                  name_scratch[name_width - 3] = '.';
                  name_scratch[name_width - 2] = '.';
                  name_scratch[name_width - 1] = '>';
                  name_scratch[name_width] = 0;
                  t2 = name_scratch;
                  nwidth = name_width;
                }
                ap_rvputs(r, "<td><a href=\"", anchor, "\">",
                          ap_escape_html(scratch, t2),
                          "</a>", pad_scratch + nwidth, NULL);
            }
            if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
                if (ar[x]->lm != -1) {
                    char time_str[MAX_STRING_LEN];
                    apr_time_exp_t ts;
                    apr_time_exp_lt(&ts, ar[x]->lm);
                    apr_strftime(time_str, &rv, MAX_STRING_LEN, 
                                 "</td><td align=\"right\">%d-%b-%Y %H:%M  ", &ts);
                    ap_rputs(time_str, r);
                }
                else {
                    ap_rputs("</td><td>&nbsp;", r);
                }
            }
            if (!(autoindex_opts & SUPPRESS_SIZE)) {
                char buf[5];
                ap_rvputs(r, "</td><td align=\"right\">",
                          apr_strfsize(ar[x]->size, buf), NULL);
            }
            if (!(autoindex_opts & SUPPRESS_DESC)) {
                if (ar[x]->desc) {
                    if (d->desc_adjust == K_ADJUST) {
                        ap_rvputs(r, "</td><td>", ar[x]->desc, NULL);
                    }
                    else {
                        ap_rvputs(r, "</td><td>", 
                                  terminate_description(d, ar[x]->desc,
                                                        autoindex_opts, 
                                                        desc_width), NULL);
                    }
                }
            }
            else {
                ap_rputs("</td><td>&nbsp;", r);
            }
            ap_rputs("</td></tr>\n", r);
        }
        else if (autoindex_opts & FANCY_INDEXING) {
            if (!(autoindex_opts & SUPPRESS_ICON)) {
                if (autoindex_opts & ICONS_ARE_LINKS) {
                    ap_rvputs(r, "<a href=\"", anchor, "\">", NULL);
                }
                if ((ar[x]->icon) || d->default_icon) {
                    ap_rvputs(r, "<img src=\"",
                              ap_escape_html(scratch,
                                             ar[x]->icon ? ar[x]->icon
                                                         : d->default_icon),
                              "\" alt=\"[", (ar[x]->alt ? ar[x]->alt : "   "),
                              "]\"", NULL);
                    if (d->icon_width) {
                        ap_rprintf(r, " width=\"%d\"", d->icon_width);
                    }
                    if (d->icon_height) {
                        ap_rprintf(r, " height=\"%d\"", d->icon_height);
                    }
                    ap_rputs(" />", r);
                }
                else {
                    ap_rputs("     ", r);
                }
                if (autoindex_opts & ICONS_ARE_LINKS) {
                    ap_rputs("</a> ", r);
                }
                else {
                    ap_rputc(' ', r);
                }
            }
            nwidth = strlen(t2);
            if (nwidth > name_width) {
                memcpy(name_scratch, t2, name_width - 3);
                name_scratch[name_width - 3] = '.';
                name_scratch[name_width - 2] = '.';
                name_scratch[name_width - 1] = '>';
                name_scratch[name_width] = 0;
                t2 = name_scratch;
                nwidth = name_width;
            }
            ap_rvputs(r, "<a href=\"", anchor, "\">",
                      ap_escape_html(scratch, t2),
                      "</a>", pad_scratch + nwidth, NULL);
            /*
             * The blank before the storm.. er, before the next field.
             */
            ap_rputs(" ", r);
            if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
                if (ar[x]->lm != -1) {
                    char time_str[MAX_STRING_LEN];
                    apr_time_exp_t ts;
                    apr_time_exp_lt(&ts, ar[x]->lm);
                    apr_strftime(time_str, &rv, MAX_STRING_LEN, 
                                "%d-%b-%Y %H:%M  ", &ts);
                    ap_rputs(time_str, r);
                }
                else {
                    /*Length="22-Feb-1998 23:42  " (see 4 lines above) */
                    ap_rputs("                   ", r);
                }
            }
            if (!(autoindex_opts & SUPPRESS_SIZE)) {
                char buf[5];
                ap_rputs(apr_strfsize(ar[x]->size, buf), r);
                ap_rputs("  ", r);
            }
            if (!(autoindex_opts & SUPPRESS_DESC)) {
                if (ar[x]->desc) {
                    ap_rputs(terminate_description(d, ar[x]->desc,
                                                   autoindex_opts,
                                                   desc_width), r);
                }
            }
            ap_rputc('\n', r);
        }
        else {
            ap_rvputs(r, "<li><a href=\"", anchor, "\"> ", t2,
                         "</a></li>\n", NULL);
        }
    }
    if (autoindex_opts & TABLE_INDEXING) {
        ap_rvputs(r, breakrow, "</table>\n", NULL);
    }
    else if (autoindex_opts & FANCY_INDEXING) {
        if (!(autoindex_opts & SUPPRESS_RULES)) {
            ap_rputs("<hr /></pre>\n", r);
        }
        else {
            ap_rputs("</pre>\n", r);
        }
    }
    else {
        ap_rputs("</ul>\n", r);
    }
}