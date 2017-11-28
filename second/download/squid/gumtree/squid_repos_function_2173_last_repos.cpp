void
ConfigParser::SetCfgLine(char *line)
{
    CfgLine = line;
    CfgPos = line;
    while (!CfgLineTokens_.empty()) {
        char *token = CfgLineTokens_.front();
        CfgLineTokens_.pop();
        free(token);
    }
}