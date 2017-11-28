static void
compileUnoptimisedREs(std::list<RegexPattern> &curlist, const SBufList &sl)
{
    int flags = REG_EXTENDED | REG_NOSUB;

    static const SBuf minus_i("-i"), plus_i("+i");
    for (auto configurationLineWord : sl) {
        if (configurationLineWord == minus_i) {
            flags |= REG_ICASE;
        } else if (configurationLineWord == plus_i) {
            flags &= ~REG_ICASE;
        } else {
            if (!compileRE(curlist, configurationLineWord.c_str() , flags))
                debugs(28, DBG_CRITICAL, "ERROR: Skipping regular expression. "
                       "Compile failed: '" << configurationLineWord << "'");
        }
    }
}