    char ch;

    /* Caller must ensure a string is next */
    assert(json->data[json->index] == '"');

    /* Skip " */
    json->index++;

    /* json->tmp is the temporary strbuf used to accumulate the
     * decoded string value. */
    strbuf_reset(json->tmp);
    while ((ch = json->data[json->index]) != '"') {
        if (!ch) {
            /* Premature end of the string */
            json_set_token_error(token, json, "unexpected end of string");
