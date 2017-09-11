    cfg->escape2char['f'] = '\f';
    cfg->escape2char['r'] = '\r';
    cfg->escape2char['u'] = 'u';          /* Unicode parsing required */


#if 0
    /* Initialise separate storage for pre-generated escape codes.
     * Escapes 0-31 map directly, 34, 92, 127 follow afterwards to
     * save memory. */
    for (i = 0 ; i < 32; i++)
        sprintf(cfg->escapes[i], "\\u%04x", i);
    strcpy(cfg->escapes[8], "\b");              /* Override simpler escapes */
    strcpy(cfg->escapes[9], "\t");
    strcpy(cfg->escapes[10], "\n");
    strcpy(cfg->escapes[12], "\f");
    strcpy(cfg->escapes[13], "\r");
    strcpy(cfg->escapes[32], "\\\"");           /* chr(34) */
    strcpy(cfg->escapes[33], "\\\\");           /* chr(92) */
    sprintf(cfg->escapes[34], "\\u%04x", 127);  /* char(127) */

    /* Initialise encoding escape lookup table */
    for (i = 0; i < 32; i++)
        cfg->char2escape[i] = cfg->escapes[i];
    for (i = 32; i < 256; i++)
        cfg->char2escape[i] = NULL;
    cfg->char2escape[34] = cfg->escapes[32];
    cfg->char2escape[92] = cfg->escapes[33];
    cfg->char2escape[127] = cfg->escapes[34];
#endif
}

/* ===== ENCODING ===== */

static void json_encode_exception(lua_State *l, json_config_t *cfg, int lindex,
                                  const char *reason)
{
    if (!cfg->encode_keep_buffer)
        strbuf_free(&cfg->encode_buf);
    luaL_error(l, "Cannot serialise %s: %s",
                  lua_typename(l, lua_type(l, lindex)), reason);
}
