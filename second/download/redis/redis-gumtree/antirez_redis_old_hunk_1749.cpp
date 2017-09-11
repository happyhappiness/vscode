        keytype = lua_type(l, -2);
        if (keytype == LUA_TNUMBER) {
            strbuf_append_char(json, '"');
            json_append_number(l, json, -2, cfg);
            strbuf_append_mem(json, "\":", 2);
        } else if (keytype == LUA_TSTRING) {
            json_append_string(l, json, -2);
            strbuf_append_char(json, ':');
        } else {
            json_encode_exception(l, cfg, -2,
                                  "table key must be a number or string");
            /* never returns */
        }

        /* table, key, value */
        json_append_data(l, cfg, json);
        lua_pop(l, 1);
        /* table, key */
    }

    strbuf_append_char(json, '}');

    cfg->current_depth--;
}

/* Serialise Lua data into JSON string. */
static void json_append_data(lua_State *l, json_config_t *cfg, strbuf_t *json)
{
    int len;

