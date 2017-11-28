static void
parse_http_header_replace(header_mangler header[])
{
    int id, i;
    char *t = NULL;

    if ((t = strtok(NULL, w_space)) == NULL) {
        debugs(3, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(3, 0, "parse_http_header_replace: missing header name.");
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
        debugs(3, 0, "parse_http_header_replace: unknown header name " << t << ".");

        return;
    }

    if (id != HDR_ENUM_END) {
        if (header[id].replacement != NULL)
            safe_free(header[id].replacement);

        header[id].replacement = xstrdup(t + strlen(t) + 1);
    } else {
        for (i = 0; i < HDR_ENUM_END; i++) {
            if (header[i].replacement != NULL)
                safe_free(header[i].replacement);

            header[i].replacement = xstrdup(t + strlen(t) + 1);
        }
    }
}