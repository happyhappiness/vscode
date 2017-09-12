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