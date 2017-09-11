
static void json_next_number_token(json_parse_t *json, json_token_t *token)
{
    const char *startptr;
    char *endptr;

    token->type = T_NUMBER;
    startptr = &json->data[json->index];
    token->value.number = strtod(&json->data[json->index], &endptr);
    if (startptr == endptr)
        json_set_token_error(token, json, "invalid number");
    else
        json->index += endptr - startptr;   /* Skip the processed number */

    return;
}

/* Fills in the token struct.
 * T_STRING will return a pointer to the json_parse_t temporary string
 * T_ERROR will leave the json->index pointer at the error.
 */
static void json_next_token(json_parse_t *json, json_token_t *token)
{
    json_token_type_t *ch2token = json->cfg->ch2token;
    int ch;

    /* Eat whitespace. FIXME: UGLY */
    token->type = ch2token[(unsigned char)json->data[json->index]];
    while (token->type == T_WHITESPACE)
        token->type = ch2token[(unsigned char)json->data[++json->index]];

    token->index = json->index;

    /* Don't advance the pointer for an error or the end */
    if (token->type == T_ERROR) {
