                                "113 Heuristic expiration");
            }
        }
        return 1;    /* Cache object is fresh (enough) */
    }

    return 0;        /* Cache object is stale */
}

/*
 * list is a comma-separated list of case-insensitive tokens, with
 * optional whitespace around the tokens.
 * The return returns 1 if the token val is found in the list, or 0
