const char *
Format::Token::scanForToken(TokenTableEntry const table[], const char *cur)
{
    for (TokenTableEntry const *lte = table; lte->configTag != NULL; ++lte) {
        debugs(46, 8, HERE << "compare tokens '" << lte->configTag << "' with '" << cur << "'");
        if (strncmp(lte->configTag, cur, strlen(lte->configTag)) == 0) {
            type = lte->tokenType;
            label = lte->configTag;
            debugs(46, 7, HERE << "Found token '" << label << "'");
            return cur + strlen(lte->configTag);
        }
    }
    return cur;
}