void
ACLFlags::parseFlags()
{
    char *nextToken;
    while ((nextToken = ConfigParser::strtokFile()) != NULL && nextToken[0] == '-') {

        //if token is the "--" break flag
        if (strcmp(nextToken, "--") == 0)
            break;

        for (const char *flg = nextToken+1; *flg!='\0'; flg++ ) {
            if (supported(*flg)) {
                makeSet(*flg);
            } else {
                debugs(28, 0, HERE << "Flag '" << *flg << "' not supported");
                self_destruct();
            }
        }
    }

    /*Regex code needs to parse -i file*/
    if ( isSet(ACL_F_REGEX_CASE))
        ConfigParser::strtokFilePutBack("-i");

    if (nextToken != NULL && strcmp(nextToken, "--") != 0 )
        ConfigParser::strtokFileUndo();
}