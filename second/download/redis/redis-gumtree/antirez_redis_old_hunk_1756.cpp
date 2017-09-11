
    /* 2 slots required:
     * .., table, value */
    json_decode_checkstack(l, json, 2);

    lua_newtable(l);

    json_next_token(json, &token);

    /* Handle empty arrays */
    if (token.type == T_ARR_END)
        return;

    for (i = 1; ; i++) {
        json_process_value(l, json, &token);
        lua_rawseti(l, -2, i);            /* arr[i] = value */

        json_next_token(json, &token);

        if (token.type == T_ARR_END)
            return;

        if (token.type != T_COMMA)
            json_throw_parse_error(l, json, "comma or array end", &token);
