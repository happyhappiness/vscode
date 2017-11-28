static struct node *
parse_objecttype(register FILE *fp, char *name) {
    register int type;
    char token[64];
    int count, length;
    struct subid SubOid[32];
    char syntax[64];
    int nexttype;
    char nexttoken[64];
    register struct node *np = NULL;
    register struct enum_list *ep = NULL;

    type = get_token(fp, token);
    if (type != SYNTAX) {
        print_error("Bad format for OBJECT TYPE", token, type);
        return 0;
    }
    np = (struct node *) xmalloc(sizeof(struct node));
    np->next = 0;
    np->enums = 0;
    type = get_token(fp, token);
    nexttype = get_token(fp, nexttoken);
    np->type = type;
    switch (type) {
    case SEQUENCE:
        strcpy(syntax, token);
        if (nexttype == OF) {
            strcat(syntax, " ");
            strcat(syntax, nexttoken);
            nexttype = get_token(fp, nexttoken);
            strcat(syntax, " ");
            strcat(syntax, nexttoken);
            nexttype = get_token(fp, nexttoken);
        }
        break;
    case INTEGER:
        strcpy(syntax, token);
        if (nexttype == LEFTBRACKET) {
            /* if there is an enumeration list, parse it */
            while ((type = get_token(fp, token)) != ENDOFFILE) {
                if (type == RIGHTBRACKET)
                    break;
                if (type == LABEL) {
                    /* this is an enumerated label */
                    if (np->enums == 0) {
                        ep = np->enums = (struct enum_list *)
                                         xmalloc(sizeof(struct enum_list));
                    } else {
                        ep->next = (struct enum_list *)
                                   xmalloc(sizeof(struct enum_list));
                        ep = ep->next;
                    }
                    ep->next = 0;
                    /* a reasonable approximation for the length */
                    ep->label = (char *) xmalloc((unsigned) strlen(token) + 1);
                    strcpy(ep->label, token);
                    type = get_token(fp, token);
                    if (type != LEFTPAREN) {
                        print_error("Expected \"(\"", token, type);
                        free_node(np);
                        return 0;
                    }
                    type = get_token(fp, token);
                    if (type != NUMBER) {
                        print_error("Expected integer", token, type);
                        free_node(np);
                        return 0;
                    }
                    ep->value = atoi(token);
                    type = get_token(fp, token);
                    if (type != RIGHTPAREN) {
                        print_error("Expected \")\"", token, type);
                        free_node(np);
                        return 0;
                    }
                }
            }
            if (type == ENDOFFILE) {
                print_error("Expected \"}\"", token, type);
                free_node(np);
                return 0;
            }
            nexttype = get_token(fp, nexttoken);
        } else if (nexttype == LEFTPAREN) {
            /* ignore the "constrained integer" for now */
            nexttype = get_token(fp, nexttoken);
            nexttype = get_token(fp, nexttoken);
            nexttype = get_token(fp, nexttoken);
        }
        break;
    case OBJID:
    case OCTETSTR:
    case NETADDR:
    case IPADDR:
    case COUNTER:
    case GAUGE:
    case TIMETICKS:
    case SNMP_OPAQUE:
    case NUL:
    case LABEL:
        strcpy(syntax, token);
        break;
    default:
        print_error("Bad syntax", token, type);
        free_node(np);
        return 0;
    }
    if (nexttype != ACCESS) {
        print_error("Should be ACCESS", nexttoken, nexttype);
        free_node(np);
        return 0;
    }
    type = get_token(fp, token);
    if (type != READONLY && type != READWRITE && type != WRITEONLY
            && type != NOACCESS) {
        print_error("Bad access type", nexttoken, nexttype);
        free_node(np);
        return 0;
    }
    type = get_token(fp, token);
    if (type != SNMP_STATUS) {
        print_error("Should be STATUS", token, nexttype);
        free_node(np);
        return 0;
    }
    type = get_token(fp, token);
    if (type != MANDATORY && type != SNMP_OPTIONAL && type != OBSOLETE && type != RECOMMENDED) {
        print_error("Bad status", token, type);
        free_node(np);
        return 0;
    }
    /* Fetch next token.  Either:
     *
     * -> EQUALS (Old MIB format)
     * -> DESCRIPTION, INDEX (New MIB format)
     */
    type = get_token(fp, token);
    if ((type != DESCRIPTION) && (type != INDEX) && (type != EQUALS)) {
        print_error("Should be DESCRIPTION, INDEX, or EQUALS", token, nexttype);
        free_node(np);
        return 0;
    }
    if (type == DESCRIPTION) {

        type = get_token(fp, token);
        if (type != QUOTE) {
            print_error("Should be Description open quote", token, nexttype);
            free_node(np);
            return 0;
        }
        /* Fetch description string */
        {
            int ReadChar;

            ReadChar = last;
            /* skip everything until closing quote */
            while ((ReadChar != '"') && (ReadChar != -1)) {
                ReadChar = getc(fp);
                if (ReadChar == '\n')
                    Line++;
            }
            last = ' ';
        }
        /* ASSERT:  Done with description. */
        type = get_token(fp, token);
    }
    if ((type != INDEX) && (type != EQUALS)) {
        print_error("Should be INDEX, or EQUALS", token, nexttype);
        free_node(np);
        return 0;
    }
    if (type == INDEX) {

        /* Scarf INDEX */

        type = get_token(fp, token);
        if (type != LEFTBRACKET) {
            print_error("Should be INDEX left brace", token, type);
            free_node(np);
            return 0;
        }
        /* Fetch description string */
        {
            int ReadChar;

            ReadChar = last;
            /* skip everything until closing quote */
            while ((ReadChar != '}') && (ReadChar != -1)) {
                ReadChar = getc(fp);
                if (ReadChar == '\n')
                    Line++;
            }
            last = ' ';
        }
        /* ASSERT:  Done with INDEX. */
        type = get_token(fp, token);
    }
    if (type != EQUALS) {
        print_error("Bad format", token, type);
        free_node(np);
        return 0;
    }
    length = getoid(fp, SubOid, 32);
    if (length > 1 && length <= 32) {
        /* just take the last pair in the oid list */
        if (SubOid[length - 2].label) {
            strncpy(np->parent, SubOid[length - 2].label, 64);
            np->parent[63] = '\0';
        }
        strncpy(np->label, name, sizeof(np->label));
        np->label[sizeof(np->label) - 1] = '\0';
        if (SubOid[length - 1].subid != -1)
            np->subid = SubOid[length - 1].subid;
        else
            print_error("Warning: This entry is pretty silly", np->label, type);
    } else {
        print_error("No end to oid", (char *) NULL, type);
        free_node(np);
        np = 0;
    }
    /* free oid array */
    for (count = 0; count < length; count++) {
        if (SubOid[count].label)
            xfree(SubOid[count].label);
        SubOid[count].label = 0;
    }
    return np;
}