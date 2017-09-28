
    /* Note: token->index is 0 based, display starting from 1 */
    luaL_error(l, "Expected %s but found %s at character %d",
               exp, found, token->index + 1);
}

static inline void json_decode_ascend(json_parse_t *json)
{
    json->current_depth--;
}

static void json_decode_descend(lua_State *l, json_parse_t *json, int slots)
{
    json->current_depth++;

    if (json->current_depth <= json->cfg->decode_max_depth &&
        lua_checkstack(l, slots)) {
        return;
    }

    strbuf_free(json->tmp);
    luaL_error(l, "Found too many nested data structures (%d) at character %d",
        json->current_depth, json->ptr - json->data);
}

static void json_parse_object_context(lua_State *l, json_parse_t *json)
{
    json_token_t token;

    /* 3 slots required:
     * .., table, key, value */
    json_decode_descend(l, json, 3);

    lua_newtable(l);

    json_next_token(json, &token);

    /* Handle empty objects */
    if (token.type == T_OBJ_END) {
        json_decode_ascend(json);
        return;
    }

    while (1) {
        if (token.type != T_STRING)
            json_throw_parse_error(l, json, "object key string", &token);
