static int
compileOptimisedREs(std::list<RegexPattern> &curlist, const SBufList &sl)
{
    std::list<RegexPattern> newlist;
    int numREs = 0;
    int flags = REG_EXTENDED | REG_NOSUB;
    int largeREindex = 0;
    char largeRE[BUFSIZ];
    *largeRE = 0;

    for (const SBuf & configurationLineWord : sl) {
        int RElen;
        RElen = configurationLineWord.length();

        static const SBuf minus_i("-i");
        static const SBuf plus_i("+i");
        if (configurationLineWord == minus_i) {
            if (flags & REG_ICASE) {
                /* optimisation of  -i ... -i */
                debugs(28, 2, "optimisation of -i ... -i" );
            } else {
                debugs(28, 2, "-i" );
                if (!compileRE(newlist, largeRE, flags))
                    return 0;
                flags |= REG_ICASE;
                largeRE[largeREindex=0] = '\0';
            }
        } else if (configurationLineWord == plus_i) {
            if ((flags & REG_ICASE) == 0) {
                /* optimisation of  +i ... +i */
                debugs(28, 2, "optimisation of +i ... +i");
            } else {
                debugs(28, 2, "+i");
                if (!compileRE(newlist, largeRE, flags))
                    return 0;
                flags &= ~REG_ICASE;
                largeRE[largeREindex=0] = '\0';
            }
        } else if (RElen + largeREindex + 3 < BUFSIZ-1) {
            debugs(28, 2, "adding RE '" << configurationLineWord << "'");
            if (largeREindex > 0) {
                largeRE[largeREindex] = '|';
                ++largeREindex;
            }
            largeRE[largeREindex] = '(';
            ++largeREindex;
            configurationLineWord.copy(largeRE+largeREindex, BUFSIZ-largeREindex);
            largeREindex += configurationLineWord.length();
            largeRE[largeREindex] = ')';
            ++largeREindex;
            largeRE[largeREindex] = '\0';
            ++numREs;
        } else {
            debugs(28, 2, "buffer full, generating new optimised RE..." );
            if (!compileRE(newlist, largeRE, flags))
                return 0;
            largeRE[largeREindex=0] = '\0';
            continue;    /* do the loop again to add the RE to largeRE */
        }
    }

    if (!compileRE(newlist, largeRE, flags))
        return 0;

    /* all was successful, so put the new list at the tail */
    curlist.splice(curlist.end(), newlist);

    debugs(28, 2, numREs << " REs are optimised into one RE.");
    if (numREs > 100) {
        debugs(28, (opt_parse_cfg_only?DBG_IMPORTANT:2), cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, (opt_parse_cfg_only?DBG_IMPORTANT:2), "WARNING: there are more than 100 regular expressions. " <<
               "Consider using less REs or use rules without expressions like 'dstdomain'.");
    }

    return 1;
}