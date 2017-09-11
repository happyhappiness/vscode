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
