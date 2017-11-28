static
#endif
struct node *
parse(FILE *fp) {
    char token[64];
    char name[64];
    int type = 1;
    struct node *np = NULL, *root = NULL;

    hash_init();

    while (type != ENDOFFILE) {
        type = get_token(fp, token);
        if (type != LABEL) {
            if (type == ENDOFFILE) {
                return root;
            }
            print_error(token, "is a reserved word", type);
            free_node_list(root);
            return NULL;
        }
        strncpy(name, token, 64);
        name[63] = '\0';
        type = get_token(fp, token);
        if (type == OBJTYPE) {
            if (root == NULL) {
                /* first link in chain */
                np = root = parse_objecttype(fp, name);
                if (np == NULL) {
                    print_error("Bad parse of object type", (char *) NULL, type);
                    return NULL;
                }
            } else {
                np->next = parse_objecttype(fp, name);
                if (np->next == NULL) {
                    print_error("Bad parse of objecttype", (char *) NULL, type);
                    free_node_list(root);
                    return NULL;
                }
            }
            /* now find end of chain */
            while (np->next)
                np = np->next;
        } else if (type == OBJID) {
            if (root == NULL) {
                /* first link in chain */
                np = root = parse_objectid(fp, name);
                if (np == NULL) {
                    print_error("Bad parse of object id", (char *) NULL, type);
                    return NULL;
                }
            } else {
                np->next = parse_objectid(fp, name);
                if (np->next == NULL) {
                    print_error("Bad parse of object type", (char *) NULL, type);
                    free_node_list(root);
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
            free_node_list(root);
            return NULL;
        }
    }
#if TEST
    {
        struct enum_list *ep;

        for (np = root; np; np = np->next) {
            printf("%s ::= { %s %d } (%d)\n", np->label, np->parent, np->subid,
                   np->type);
            if (np->enums) {
                printf("Enums: \n");
                for (ep = np->enums; ep; ep = ep->next) {
                    printf("%s(%d)\n", ep->label, ep->value);
                }
            }
        }
    }
#endif /* TEST */
    return root;
}