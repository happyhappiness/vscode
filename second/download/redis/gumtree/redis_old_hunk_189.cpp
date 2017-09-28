
    /* Note: token->index is 0 based, display starting from 1 */
    luaL_error(l, "Expected %s but found %s at character %d",
               exp, found, token->index + 1);
}

static void json_decode_checkstack(lua_State *l, json_parse_t *json, int n)
{
    if (lua_checkstack(l, n))
        return;

    strbuf_free(json->tmp);
    luaL_error(l, "Too many nested data structures");
}

static void json_parse_object_context(lua_State *l, json_parse_t *json)
{
    json_token_t token;

    /* 3 slots required:
     * .., table, key, value */
    json_decode_checkstack(l, json, 3);

    lua_newtable(l);

    json_next_token(json, &token);

    /* Handle empty objects */
    if (token.type == T_OBJ_END) {
        return;
    }

    while (1) {
        if (token.type != T_STRING)
            json_throw_parse_error(l, json, "object key string", &token);
