static void lua_json_decode(lua_State *l, const char *json_text, int json_len)
{
    json_parse_t json;
    json_token_t token;

    json.cfg = json_fetch_config(l);
    json.data = json_text;
    json.index = 0;

    /* Ensure the temporary buffer can hold the entire string.
     * This means we no longer need to do length checks since the decoded
     * string must be smaller than the entire json string */
    json.tmp = strbuf_new(json_len);

    json_next_token(&json, &token);
    json_process_value(l, &json, &token);

    /* Ensure there is no more input left */
    json_next_token(&json, &token);

    if (token.type != T_END)
        json_throw_parse_error(l, &json, "the end", &token);

    strbuf_free(json.tmp);
}