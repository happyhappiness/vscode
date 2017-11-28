char *
ConfigParser::NextQuotedOrToEol()
{
    ParseQuotedOrToEol_ = true;
    char *token = NextToken();
    ParseQuotedOrToEol_ = false;

    // Assume end of current config line
    // Close all open configuration files for this config line
    while (!CfgFiles.empty()) {
        ConfigParser::CfgFile *wordfile = CfgFiles.top();
        CfgFiles.pop();
        delete wordfile;
    }

    return token;
}