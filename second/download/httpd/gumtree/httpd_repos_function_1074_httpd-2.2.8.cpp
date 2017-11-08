static int imap_handler_internal(request_rec *r)
{
    char input[MAX_STRING_LEN];
    char *directive;
    char *value;
    char *href_text;
    char *base;
    char *redirect;
    char *mapdflt;
    char *closest = NULL;
    double closest_yet = -1;
    apr_status_t status;

    double testpoint[2];
    double pointarray[MAXVERTS + 1][2];
    int vertex;

    char *string_pos;
    int showmenu = 0;

    imap_conf_rec *icr;

    char *imap_menu;
    char *imap_default;
    char *imap_base;

    ap_configfile_t *imap;

    icr = ap_get_module_config(r->per_dir_config, &imagemap_module);

    imap_menu = icr->imap_menu ? icr->imap_menu : IMAP_MENU_DEFAULT;
    imap_default = icr->imap_default
      ?  icr->imap_default : IMAP_DEFAULT_DEFAULT;
    imap_base = icr->imap_base ? icr->imap_base : IMAP_BASE_DEFAULT;

    status = ap_pcfg_openfile(&imap, r->pool, r->filename);

    if (status != APR_SUCCESS) {
        return HTTP_NOT_FOUND;
    }

    base = imap_url(r, NULL, imap_base);         /* set base according
                                                    to default */
    if (!base) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    mapdflt = imap_url(r, NULL, imap_default);   /* and default to
                                                    global default */
    if (!mapdflt) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    testpoint[X] = get_x_coord(r->args);
    testpoint[Y] = get_y_coord(r->args);

    if ((testpoint[X] == -1 || testpoint[Y] == -1) ||
        (testpoint[X] == 0 && testpoint[Y] == 0)) {
        /* if either is -1 or if both are zero (new Lynx) */
        /* we don't have valid coordinates */
        testpoint[X] = -1;
        testpoint[Y] = -1;
        if (strncasecmp(imap_menu, "none", 2)) {
            showmenu = 1;       /* show the menu _unless_ ImapMenu is
                                   'none' or 'no' */
        }
    }

    if (showmenu) {             /* send start of imagemap menu if
                                   we're going to */
        menu_header(r, imap_menu);
    }

    while (!ap_cfg_getline(input, sizeof(input), imap)) {
        if (!input[0]) {
            if (showmenu) {
                menu_blank(r, imap_menu);
            }
            continue;
        }

        if (input[0] == '#') {
            if (showmenu) {
                menu_comment(r, imap_menu, input + 1);
            }
            continue;
        }                       /* blank lines and comments are ignored
                                   if we aren't printing a menu */

        /* find the first two space delimited fields, recall that
         * ap_cfg_getline has removed leading/trailing whitespace.
         *
         * note that we're tokenizing as we go... if we were to use the
         * ap_getword() class of functions we would end up allocating extra
         * memory for every line of the map file
         */
        string_pos = input;
        if (!*string_pos) {   /* need at least two fields */
            goto need_2_fields;
        }

        directive = string_pos;
        while (*string_pos && !apr_isspace(*string_pos)) {   /* past directive */
            ++string_pos;
        }
        if (!*string_pos) {   /* need at least two fields */
            goto need_2_fields;
        }
        *string_pos++ = '\0';

        if (!*string_pos) {   /* need at least two fields */
            goto need_2_fields;
        }
        while(*string_pos && apr_isspace(*string_pos)) { /* past whitespace */
            ++string_pos;
        }

        value = string_pos;
        while (*string_pos && !apr_isspace(*string_pos)) {   /* past value */
            ++string_pos;
        }
        if (apr_isspace(*string_pos)) {
            *string_pos++ = '\0';
        }
        else {
            /* end of input, don't advance past it */
            *string_pos = '\0';
        }

        if (!strncasecmp(directive, "base", 4)) {       /* base, base_uri */
            base = imap_url(r, NULL, value);
            if (!base) {
                goto menu_bail;
            }
            continue;           /* base is never printed to a menu */
        }

        read_quoted(&string_pos, &href_text);

        if (!strcasecmp(directive, "default")) {        /* default */
            mapdflt = imap_url(r, NULL, value);
            if (!mapdflt) {
                goto menu_bail;
            }
            if (showmenu) {     /* print the default if there's a menu */
                redirect = imap_url(r, base, mapdflt);
                if (!redirect) {
                    goto menu_bail;
                }
                menu_default(r, imap_menu, redirect,
                             href_text ? href_text : mapdflt);
            }
            continue;
        }

        vertex = 0;
        while (vertex < MAXVERTS &&
               sscanf(string_pos, "%lf%*[, ]%lf",
                      &pointarray[vertex][X], &pointarray[vertex][Y]) == 2) {
            /* Now skip what we just read... we can't use ANSIism %n */
            while (apr_isspace(*string_pos)) {      /* past whitespace */
                string_pos++;
            }
            while (apr_isdigit(*string_pos)) {      /* and the 1st number */
                string_pos++;
            }
            string_pos++;       /* skip the ',' */
            while (apr_isspace(*string_pos)) {      /* past any more whitespace */
                string_pos++;
            }
            while (apr_isdigit(*string_pos)) {      /* 2nd number */
                string_pos++;
            }
            vertex++;
        }                       /* so long as there are more vertices to
                                   read, and we have room, read them in.
                                   We start where we left off of the last
                                   sscanf, not at the beginning. */

        pointarray[vertex][X] = -1;     /* signals the end of vertices */

        if (showmenu) {
            if (!href_text) {
                read_quoted(&string_pos, &href_text);     /* href text could
                                                             be here instead */
            }
            redirect = imap_url(r, base, value);
            if (!redirect) {
                goto menu_bail;
            }
            menu_directive(r, imap_menu, redirect,
                           href_text ? href_text : value);
            continue;
        }
        /* note that we don't make it past here if we are making a menu */

        if (testpoint[X] == -1 || pointarray[0][X] == -1) {
            continue;           /* don't try the following tests if testpoints
                                   are invalid, or if there are no
                                   coordinates */
        }

        if (!strcasecmp(directive, "poly")) {   /* poly */

            if (pointinpoly(testpoint, pointarray)) {
                ap_cfg_closefile(imap);
                redirect = imap_url(r, base, value);
                if (!redirect) {
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                return (imap_reply(r, redirect));
            }
            continue;
        }

        if (!strcasecmp(directive, "circle")) {         /* circle */

            if (pointincircle(testpoint, pointarray)) {
                ap_cfg_closefile(imap);
                redirect = imap_url(r, base, value);
                if (!redirect) {
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                return (imap_reply(r, redirect));
            }
            continue;
        }

        if (!strcasecmp(directive, "rect")) {   /* rect */

            if (pointinrect(testpoint, pointarray)) {
                ap_cfg_closefile(imap);
                redirect = imap_url(r, base, value);
                if (!redirect) {
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                return (imap_reply(r, redirect));
            }
            continue;
        }

        if (!strcasecmp(directive, "point")) {  /* point */

            if (is_closer(testpoint, pointarray, &closest_yet)) {
                closest = apr_pstrdup(r->pool, value);
            }

            continue;
        }                       /* move on to next line whether it's
                                   closest or not */

    }                           /* nothing matched, so we get another line! */

    ap_cfg_closefile(imap);        /* we are done with the map file; close it */

    if (showmenu) {
        menu_footer(r);         /* finish the menu and we are done */
        return OK;
    }

    if (closest) {             /* if a 'point' directive has been seen */
        redirect = imap_url(r, base, closest);
        if (!redirect) {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        return (imap_reply(r, redirect));
    }

    if (mapdflt) {             /* a default should be defined, even if
                                  only 'nocontent' */
        redirect = imap_url(r, base, mapdflt);
        if (!redirect) {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        return (imap_reply(r, redirect));
    }

    return HTTP_INTERNAL_SERVER_ERROR;        /* If we make it this far,
                                                 we failed. They lose! */

need_2_fields:
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                "map file %s, line %d syntax error: requires at "
                "least two fields", r->uri, imap->line_number);
    /* fall through */
menu_bail:
    ap_cfg_closefile(imap);
    if (showmenu) {
        /* There's not much else we can do ... we've already sent the headers
         * to the client.
         */
        ap_rputs("\n\n[an internal server error occured]\n", r);
        menu_footer(r);
        return OK;
    }
    return HTTP_INTERNAL_SERVER_ERROR;
}