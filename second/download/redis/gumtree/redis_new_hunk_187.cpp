/* JSON numbers should take the following form:
 *      -?(0|[1-9]|[1-9][0-9]+)(.[0-9]+)?([eE][-+]?[0-9]+)?
 *
 * json_next_number_token() uses strtod() which allows other forms:
 * - numbers starting with '+'
 * - NaN, -NaN, infinity, -infinity
 * - hexadecimal numbers
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
    const char *p = json->ptr;

    /* Reject numbers starting with + */
    if (*p == '+')
        return 1;

    /* Skip minus sign if it exists */
    if (*p == '-')
        p++;

    /* Reject numbers starting with 0x, or leading zeros */
    if (*p == '0') {
        int ch2 = *(p + 1);

        if ((ch2 | 0x20) == 'x' ||          /* Hex */
            ('0' <= ch2 && ch2 <= '9'))     /* Leading zero */
            return 1;

        return 0;
    } else if (*p <= '9') {
        return 0;                           /* Ordinary number */
    }

    /* Reject inf/nan */
    if (!strncasecmp(p, "inf", 3))
        return 1;
    if (!strncasecmp(p, "nan", 3))
        return 1;

    /* Pass all other numbers which may still be invalid, but
     * strtod() will catch them. */
    return 0;
}

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
        json_set_token_error(token, json, "invalid token");
        return;
    }
