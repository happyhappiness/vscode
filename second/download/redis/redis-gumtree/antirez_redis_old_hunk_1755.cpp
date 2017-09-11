
        json_next_token(json, &token);

        if (token.type == T_OBJ_END)
            return;

        if (token.type != T_COMMA)
            json_throw_parse_error(l, json, "comma or object end", &token);
