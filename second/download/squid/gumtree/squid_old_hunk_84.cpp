{
    cfg->parsePoolAccess(LegacyParser);
}

#endif

#if HTTP_VIOLATIONS
static void
dump_http_header_access(StoreEntry * entry, const char *name, header_mangler header[])
{
    int i;

    for (i = 0; i < HDR_ENUM_END; i++) {
        if (header[i].access_list != NULL) {
            storeAppendPrintf(entry, "%s ", name);
            dump_acl_access(entry, httpHeaderNameById(i),
                            header[i].access_list);
        }
    }
}

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

static void
free_http_header_access(header_mangler header[])
{
    int i;

    for (i = 0; i < HDR_ENUM_END; i++) {
        free_acl_access(&header[i].access_list);
    }
}

static void
dump_http_header_replace(StoreEntry * entry, const char *name, header_mangler
                         header[])
{
    int i;

    for (i = 0; i < HDR_ENUM_END; i++) {
        if (NULL == header[i].replacement)
            continue;

        storeAppendPrintf(entry, "%s %s %s\n", name, httpHeaderNameById(i),
                          header[i].replacement);
    }
}

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

static void
free_http_header_replace(header_mangler header[])
{
    int i;

    for (i = 0; i < HDR_ENUM_END; i++) {
        if (header[i].replacement != NULL)
            safe_free(header[i].replacement);
    }
}

#endif

static void
dump_cachedir(StoreEntry * entry, const char *name, SquidConfig::_cacheSwap swap)
{
    SwapDir *s;
    int i;
    assert (entry);

    for (i = 0; i < swap.n_configured; i++) {
        s = dynamic_cast<SwapDir *>(swap.swapDirs[i].getRaw());
        if (!s) continue;
        storeAppendPrintf(entry, "%s %s %s", name, s->type(), s->path);
        s->dump(*entry);
        storeAppendPrintf(entry, "\n");
    }
