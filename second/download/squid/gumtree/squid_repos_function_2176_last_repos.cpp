char *
ConfigParser::NextToken()
{
    char *token = NULL;
    if ((token = ConfigParser::Undo())) {
        debugs(3, 6, "TOKEN (undone): " << token);
        return token;
    }

    do {
        while (token == NULL && !CfgFiles.empty()) {
            ConfigParser::CfgFile *wordfile = CfgFiles.top();
            token = wordfile->parse(LastTokenType);
            if (!token) {
                assert(!wordfile->isOpen());
                CfgFiles.pop();
                debugs(3, 4, "CfgFiles.pop " << wordfile->filePath);
                delete wordfile;
            }
        }

        if (!token)
            token = NextElement(LastTokenType);

        if (token &&  LastTokenType == ConfigParser::FunctionParameters) {
            //Disable temporary preview mode, we need to parse function parameters
            const bool savePreview = ConfigParser::PreviewMode_;
            ConfigParser::PreviewMode_ = false;

            char *path = NextToken();
            if (LastTokenType != ConfigParser::QuotedToken) {
                debugs(3, DBG_CRITICAL, "FATAL: Quoted filename missing: " << token);
                self_destruct();
                return NULL;
            }

            // The next token in current cfg file line must be a ")"
            char *end = NextToken();
            ConfigParser::PreviewMode_ = savePreview;
            if (LastTokenType != ConfigParser::SimpleToken || strcmp(end, ")") != 0) {
                debugs(3, DBG_CRITICAL, "FATAL: missing ')' after " << token << "(\"" << path << "\"");
                self_destruct();
                return NULL;
            }

            if (CfgFiles.size() > 16) {
                debugs(3, DBG_CRITICAL, "FATAL: can't open %s for reading parameters: includes are nested too deeply (>16)!\n" << path);
                self_destruct();
                return NULL;
            }

            ConfigParser::CfgFile *wordfile = new ConfigParser::CfgFile();
            if (!path || !wordfile->startParse(path)) {
                debugs(3, DBG_CRITICAL, "FATAL: Error opening config file: " << token);
                delete wordfile;
                self_destruct();
                return NULL;
            }
            CfgFiles.push(wordfile);
            token = NULL;
        }
    } while (token == NULL && !CfgFiles.empty());

    return token;
}