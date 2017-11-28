                    return NULL;
                }
            } else {
                np->next = parse_objecttype(fp, name);
                if (np->next == NULL) {
                    print_error("Bad parse of objecttype", (char *) NULL, type);
                    return NULL;
                }
            }
            /* now find end of chain */
            while (np->next)
                np = np->next;
