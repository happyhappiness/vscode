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
