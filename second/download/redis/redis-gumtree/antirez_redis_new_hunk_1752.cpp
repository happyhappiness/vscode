
static void json_next_number_token(json_parse_t *json, json_token_t *token)
{
    char *endptr;

    token->type = T_NUMBER;
    token->value.number = fpconv_strtod(json->ptr, &endptr);
    if (json->ptr == endptr)
        json_set_token_error(token, json, "invalid number");
    else
        json->ptr = endptr;     /* Skip the processed number */

    return;
}

/* Fills in the token struct.
 * T_STRING will return a pointer to the json_parse_t temporary string
 * T_ERROR will leave the json->ptr pointer at the error.
 */
static void json_next_token(json_parse_t *json, json_token_t *token)
{
    const json_token_type_t *ch2token = json->cfg->ch2token;
    int ch;

    /* Eat whitespace. */
    while (1) {
        ch = (unsigned char)*(json->ptr);
        token->type = ch2token[ch];
        if (token->type != T_WHITESPACE)
            break;
        json->ptr++;
    }

    /* Store location of new token. Required when throwing errors
     * for unexpected tokens (syntax errors). */
    token->index = json->ptr - json->data;

    /* Don't advance the pointer for an error or the end */
    if (token->type == T_ERROR) {
