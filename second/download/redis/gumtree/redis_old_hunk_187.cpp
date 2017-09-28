/* JSON numbers should take the following form:
 *      -?(0|[1-9]|[1-9][0-9]+)(.[0-9]+)?([eE][-+]?[0-9]+)?
 *
 * json_next_number_token() uses strtod() which allows other forms:
 * - numbers starting with '+'
 * - NaN, -NaN, infinity, -infinity
 * - hexidecimal numbers
 * - numbers with leading zeros
 *
 * json_is_invalid_number() detects "numbers" which may pass strtod()'s
 * error checking, but should not be allowed with strict JSON.
 *
 * json_is_invalid_number() may pass numbers which cause strtod()
 * to generate an error.
 */
static int json_is_invalid_number(json_parse_t *json)
{
    int i = json->index;

    /* Reject numbers starting with + */
    if (json->data[i] == '+')
        return 1;

    /* Skip minus sign if it exists */
    if (json->data[i] == '-')
        i++;

    /* Reject numbers starting with 0x, or leading zeros */
    if (json->data[i] == '0') {
        int ch2 = json->data[i + 1];

        if ((ch2 | 0x20) == 'x' ||          /* Hex */
            ('0' <= ch2 && ch2 <= '9'))     /* Leading zero */
            return 1;

        return 0;
    } else if (json->data[i] <= '9') {
        return 0;                           /* Ordinary number */
    }


    /* Reject inf/nan */
    if (!strncasecmp(&json->data[i], "inf", 3))
        return 1;
    if (!strncasecmp(&json->data[i], "nan", 3))
        return 1;

    /* Pass all other numbers which may still be invalid, but
     * strtod() will catch them. */
    return 0;
}

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
        json_set_token_error(token, json, "invalid token");
        return;
    }
