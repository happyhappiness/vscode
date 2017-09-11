        max > items * cfg->encode_sparse_ratio &&
        max > cfg->encode_sparse_safe) {
        if (!cfg->encode_sparse_convert)
            json_encode_exception(l, cfg, -1, "excessively sparse array");

        return -1;
    }

    return max;
}

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

static void json_append_data(lua_State *l, json_config_t *cfg, strbuf_t *json);

/* json_append_array args:
 * - lua_State
 * - JSON strbuf
 * - Size of passwd Lua array (top of stack) */
static void json_append_array(lua_State *l, json_config_t *cfg, strbuf_t *json,
                              int array_length)
{
    int comma, i;

    json_encode_descend(l, cfg);

    strbuf_append_char(json, '[');

    comma = 0;
