static int
parse_asntype(FILE *fp)
{
    int type;
    char token[64];

    type = get_token(fp, token);
    if (type != SEQUENCE) {
        print_error("Not a sequence", token, type); /* should we handle this */
        return ENDOFFILE;
    }
    while ((type = get_token(fp, token)) != ENDOFFILE) {
        if (type == RIGHTBRACKET)
            return type;
    }
    print_error("Expected \"}\"", token, type);
    return ENDOFFILE;
}