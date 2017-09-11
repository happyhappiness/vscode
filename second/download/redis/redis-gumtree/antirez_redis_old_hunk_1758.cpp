        json_throw_parse_error(l, &json, "the end", &token);

    strbuf_free(json.tmp);
}

static int json_decode(lua_State *l)
{
    const char *json;
    size_t len;

    json_verify_arg_count(l, 1);

    json = luaL_checklstring(l, 1, &len);

    /* Detect Unicode other than UTF-8 (see RFC 4627, Sec 3)
     *
     * CJSON can support any simple data type, hence only the first
     * character is guaranteed to be ASCII (at worst: '"'). This is
     * still enough to detect whether the wrong encoding is in use. */
    if (len >= 2 && (!json[0] || !json[1]))
        luaL_error(l, "JSON parser does not support UTF-16 or UTF-32");

    lua_json_decode(l, json, len);

    return 1;
}

/* ===== INITIALISATION ===== */

int luaopen_cjson(lua_State *l)
{
    luaL_Reg reg[] = {
        { "encode", json_encode },
        { "decode", json_decode },
        { "encode_sparse_array", json_cfg_encode_sparse_array },
        { "encode_max_depth", json_cfg_encode_max_depth },
        { "encode_number_precision", json_cfg_encode_number_precision },
        { "encode_keep_buffer", json_cfg_encode_keep_buffer },
        { "refuse_invalid_numbers", json_cfg_refuse_invalid_numbers },
        { NULL, NULL }
    };

    /* Use json_fetch_config as a pointer.
     * It's faster than using a config string, and more unique */
    lua_pushlightuserdata(l, &json_config_key);
    json_create_config(l);
    lua_settable(l, LUA_REGISTRYINDEX);

    luaL_register(l, "cjson", reg);

    /* Set cjson.null */
    lua_pushlightuserdata(l, NULL);
    lua_setfield(l, -2, "null");

    /* Set cjson.version */
    lua_pushliteral(l, VERSION);
    lua_setfield(l, -2, "version");

    /* Return cjson table */
    return 1;
}

/* vi:ai et sw=4 ts=4:
 */
