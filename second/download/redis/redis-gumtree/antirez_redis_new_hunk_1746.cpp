    cfg->escape2char['f'] = '\f';
    cfg->escape2char['r'] = '\r';
    cfg->escape2char['u'] = 'u';          /* Unicode parsing required */
}

/* ===== ENCODING ===== */

static void json_encode_exception(lua_State *l, json_config_t *cfg, strbuf_t *json, int lindex,
                                  const char *reason)
{
    if (!cfg->encode_keep_buffer)
        strbuf_free(json);
    luaL_error(l, "Cannot serialise %s: %s",
                  lua_typename(l, lua_type(l, lindex)), reason);
}
