static void
parse_http_header_access(header_mangler header[])
{
    int id, i;
    char *t = NULL;

    if ((t = strtok(NULL, w_space)) == NULL) {
        debugs(3, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(3, 0, "parse_http_header_access: missing header name.");
        return;
    }

    /* Now lookup index of header. */
    id = httpHeaderIdByNameDef(t, strlen(t));

    if (strcmp(t, "All") == 0)
        id = HDR_ENUM_END;
    else if (strcmp(t, "Other") == 0)
        id = HDR_OTHER;
    else if (id == -1) {
        debugs(3, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(3, 0, "parse_http_header_access: unknown header name '" << t << "'");
        return;
    }

    if (id != HDR_ENUM_END) {
        parse_acl_access(&header[id].access_list);
    } else {
        char *next_string = t + strlen(t) - 1;
        *next_string = 'A';
        *(next_string + 1) = ' ';

        for (i = 0; i < HDR_ENUM_END; i++) {
            char *new_string = xstrdup(next_string);
            strtok(new_string, w_space);
            parse_acl_access(&header[i].access_list);
            safe_free(new_string);
        }
    }
}