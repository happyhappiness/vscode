static int
getoid(register FILE *fp, register struct subid *SubOid, int length)
{
    register int count;
    int type;
    char token[128];
    register char *cp;

    if ((type = get_token(fp, token)) != LEFTBRACKET) {
        print_error("Expected \"{\"", token, type);
        return 0;
    }
    type = get_token(fp, token);
    for (count = 0; count < length; count++, SubOid++) {
        SubOid->label = 0;
        SubOid->subid = -1;
        if (type == RIGHTBRACKET) {
            return count;
        } else if (type != LABEL && type != NUMBER) {
            print_error("Not valid for object identifier", token, type);
            return 0;
        }
        if (type == LABEL) {
            /* this entry has a label */
            cp = (char *) xmalloc((unsigned) strlen(token) + 1);
            strcpy(cp, token);
            SubOid->label = cp;
            type = get_token(fp, token);
            if (type == LEFTPAREN) {
                type = get_token(fp, token);
                if (type == NUMBER) {
                    SubOid->subid = atoi(token);
                    if ((type = get_token(fp, token)) != RIGHTPAREN) {
                        print_error("Unexpected a closing parenthesis", token, type);
                        return 0;
                    }
                } else {
                    print_error("Expected a number", token, type);
                    return 0;
                }
            } else {
                continue;
            }
        } else {
            /* this entry  has just an integer sub-identifier */
            SubOid->subid = atoi(token);
        }
        type = get_token(fp, token);
    }
    return count;


}