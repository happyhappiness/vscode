                    return NULL;
                }
            } else {
                np->next = parse_objectid(fp, name);
                if (np->next == NULL) {
                    print_error("Bad parse of object type", (char *) NULL, type);
                    return NULL;
                }
            }
            /* now find end of chain */
            while (np->next)
                np = np->next;
        } else if (type == EQUALS) {
            type = parse_asntype(fp);
        } else if (type == ENDOFFILE) {
            break;
        } else {
            print_error("Bad operator", (char *) NULL, type);
            return NULL;
        }
    }
#ifdef TEST
    {
        struct enum_list *ep;

        for (np = root; np; np = np->next) {
            printf("%s ::= { %s %d } (%d)\n", np->label, np->parent, np->subid,
                   np->type);
