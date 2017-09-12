static void json_encode_descend(lua_State *l, json_config_t *cfg)
{
    cfg->current_depth++;

    if (cfg->current_depth > cfg->encode_max_depth) {
        if (!cfg->encode_keep_buffer)
            strbuf_free(&cfg->encode_buf);
        luaL_error(l, "Cannot serialise, excessive nesting (%d)",
                   cfg->current_depth);
    }
}