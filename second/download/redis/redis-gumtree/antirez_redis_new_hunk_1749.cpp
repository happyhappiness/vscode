        keytype = lua_type(l, -2);
        if (keytype == LUA_TNUMBER) {
            strbuf_append_char(json, '"');
            json_append_number(l, cfg, json, -2);
            strbuf_append_mem(json, "\":", 2);
        } else if (keytype == LUA_TSTRING) {
            json_append_string(l, json, -2);
            strbuf_append_char(json, ':');
        } else {
            json_encode_exception(l, cfg, json, -2,
                                  "table key must be a number or string");
            /* never returns */
        }

        /* table, key, value */
        json_append_data(l, cfg, current_depth, json);
        lua_pop(l, 1);
        /* table, key */
    }

    strbuf_append_char(json, '}');
}

/* Serialise Lua data into JSON string. */
static void json_append_data(lua_State *l, json_config_t *cfg,
                             int current_depth, strbuf_t *json)
{
    int len;

