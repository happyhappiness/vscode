            comma = 1;

        /* table, key, value */
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

    switch (lua_type(l, -1)) {
    case LUA_TSTRING:
        json_append_string(l, json, -1);
        break;
    case LUA_TNUMBER:
        json_append_number(l, json, -1, cfg);
        break;
    case LUA_TBOOLEAN:
        if (lua_toboolean(l, -1))
            strbuf_append_mem(json, "true", 4);
        else
            strbuf_append_mem(json, "false", 5);
        break;
    case LUA_TTABLE:
        len = lua_array_length(l, cfg);
        if (len > 0)
            json_append_array(l, cfg, json, len);
        else
            json_append_object(l, cfg, json);
        break;
    case LUA_TNIL:
        strbuf_append_mem(json, "null", 4);
        break;
    case LUA_TLIGHTUSERDATA:
        if (lua_touserdata(l, -1) == NULL) {
            strbuf_append_mem(json, "null", 4);
            break;
        }
    default:
        /* Remaining types (LUA_TFUNCTION, LUA_TUSERDATA, LUA_TTHREAD,
         * and LUA_TLIGHTUSERDATA) cannot be serialised */
        json_encode_exception(l, cfg, -1, "type not supported");
        /* never returns */
    }
}

static int json_encode(lua_State *l)
{
    json_config_t *cfg;
    char *json;
    int len;

    /* Can't use json_verify_arg_count() since we need to ensure
     * there is only 1 argument */
    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");

    cfg = json_fetch_config(l);
    cfg->current_depth = 0;

    /* Reset the persistent buffer if it exists.
     * Otherwise allocate a new buffer. */
    if (strbuf_allocated(&cfg->encode_buf))
        strbuf_reset(&cfg->encode_buf);
    else
        strbuf_init(&cfg->encode_buf, 0);

    json_append_data(l, cfg, &cfg->encode_buf);
    json = strbuf_string(&cfg->encode_buf, &len);

    lua_pushlstring(l, json, len);

    if (!cfg->encode_keep_buffer)
        strbuf_free(&cfg->encode_buf);

    return 1;
}

/* ===== DECODING ===== */

