static int
compileOptimisedREs(RegexList **curlist, wordlist * wl)
{
    RegexList **Tail;
    RegexList *newlist;
    RegexList **newlistp;
    int numREs = 0;
    int flags = REG_EXTENDED | REG_NOSUB;
    int largeREindex = 0;
    char largeRE[BUFSIZ];

    newlist = NULL;
    newlistp = &newlist;

    largeRE[0] = '\0';

    while (wl != NULL) {
        int RElen;
        RElen = strlen( wl->key );

        if (strcmp(wl->key, "-i") == 0) {
            if (flags & REG_ICASE) {
                /* optimisation of  -i ... -i */
                debugs(28, 2, "compileOptimisedREs: optimisation of -i ... -i" );
            } else {
                debugs(28, 2, "compileOptimisedREs: -i" );
                newlistp = compileRE( newlistp, largeRE, flags );
                if (newlistp == NULL) {
                    aclDestroyRegexList( newlist );
                    return 0;
                }
                flags |= REG_ICASE;
                largeRE[largeREindex=0] = '\0';
            }
        } else if (strcmp(wl->key, "+i") == 0) {
            if ((flags & REG_ICASE) == 0) {
                /* optimisation of  +i ... +i */
                debugs(28, 2, "compileOptimisedREs: optimisation of +i ... +i");
            } else {
                debugs(28, 2, "compileOptimisedREs: +i");
                newlistp = compileRE( newlistp, largeRE, flags );
                if (newlistp == NULL) {
                    aclDestroyRegexList( newlist );
                    return 0;
                }
                flags &= ~REG_ICASE;
                largeRE[largeREindex=0] = '\0';
            }
        } else if (RElen + largeREindex + 3 < BUFSIZ-1) {
            debugs(28, 2, "compileOptimisedREs: adding RE '" << wl->key << "'");
            if (largeREindex > 0) {
                largeRE[largeREindex] = '|';
                ++largeREindex;
            }
            largeRE[largeREindex] = '(';
            ++largeREindex;
            for (char * t = wl->key; *t != '\0'; ++t) {
                largeRE[largeREindex] = *t;
                ++largeREindex;
            }
            largeRE[largeREindex] = ')';
            ++largeREindex;
            largeRE[largeREindex] = '\0';
            ++numREs;
        } else {
            debugs(28, 2, "compileOptimisedREs: buffer full, generating new optimised RE..." );
            newlistp = compileRE( newlistp, largeRE, flags );
            if (newlistp == NULL) {
                aclDestroyRegexList( newlist );
                return 0;
            }
            largeRE[largeREindex=0] = '\0';
            continue;    /* do the loop again to add the RE to largeRE */
        }
        wl = wl->next;
    }

    newlistp = compileRE( newlistp, largeRE, flags );
    if (newlistp == NULL) {
        aclDestroyRegexList( newlist );
        return 0;
    }

    /* all was successful, so put the new list at the tail */
    if (*curlist == NULL) {
        *curlist = newlist;
    } else {
        for (Tail = curlist; *Tail != NULL; Tail = &((*Tail)->next))
            ;
        (*Tail) = newlist;
    }

    debugs(28, 2, "compileOptimisedREs: " << numREs << " REs are optimised into one RE.");
    if (numREs > 100) {
        debugs(28, (opt_parse_cfg_only?DBG_IMPORTANT:2), "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, (opt_parse_cfg_only?DBG_IMPORTANT:2), "WARNING: there are more than 100 regular expressions. " <<
               "Consider using less REs or use rules without expressions like 'dstdomain'.");
    }

    return 1;
}