
    /* Encode excessively sparse arrays as objects (if enabled) */
    if (cfg->encode_sparse_ratio > 0 &&
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
    for (i = 1; i <= array_length; i++) {
        if (comma)
            strbuf_append_char(json, ',');
        else
            comma = 1;

        lua_rawgeti(l, -1, i);
        json_append_data(l, cfg, json);
        lua_pop(l, 1);
    }

    strbuf_append_char(json, ']');

    cfg->current_depth--;
}

static void json_append_number(lua_State *l, strbuf_t *json, int index,
                               json_config_t *cfg)
{
    double num = lua_tonumber(l, index);

    if (cfg->encode_refuse_badnum && (isinf(num) || isnan(num)))
        json_encode_exception(l, cfg, index, "must not be NaN or Inf");

    /* Lowest double printed with %.14g is 21 characters long:
     * -1.7976931348623e+308
     *
     * Use 32 to include the \0, and a few extra just in case..
     */
    strbuf_append_fmt(json, 32, cfg->number_fmt, num);
}

static void json_append_object(lua_State *l, json_config_t *cfg,
                               strbuf_t *json)
{
    int comma, keytype;

    json_encode_descend(l, cfg);

    /* Object */
    strbuf_append_char(json, '{');

    lua_pushnil(l);
    /* table, startkey */
    comma = 0;
