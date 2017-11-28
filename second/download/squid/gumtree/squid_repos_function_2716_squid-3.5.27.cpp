char *
ConfigParser::TokenParse(const char * &nextToken, ConfigParser::TokenType &type)
{
    if (!nextToken || *nextToken == '\0')
        return NULL;
    type = ConfigParser::SimpleToken;
    nextToken += strspn(nextToken, w_space);

    if (*nextToken == '#')
        return NULL;

    if (ConfigParser::RecognizeQuotedValues && (*nextToken == '"' || *nextToken == '\'')) {
        type = ConfigParser::QuotedToken;
        char *token = xstrdup(UnQuote(nextToken, &nextToken));
        CfgLineTokens_.push(token);
        return token;
    }

    const char *tokenStart = nextToken;
    const char *sep;
    if (ConfigParser::ParseQuotedOrToEol_)
        sep = "\n";
    else if (ConfigParser::RecognizeQuotedPair_)
        sep = w_space "\\";
    else if (!ConfigParser::RecognizeQuotedValues || *nextToken == '(')
        sep = w_space;
    else
        sep = w_space "(";
    nextToken += strcspn(nextToken, sep);

    while (ConfigParser::RecognizeQuotedPair_ && *nextToken == '\\') {
        // NP: do not permit \0 terminator to be escaped.
        if (*(nextToken+1) && *(nextToken+1) != '\r' && *(nextToken+1) != '\n') {
            nextToken += 2; // skip the quoted-pair (\-escaped) character
            nextToken += strcspn(nextToken, sep);
        } else {
            debugs(3, DBG_CRITICAL, "FATAL: Unescaped '\' character in regex pattern: " << tokenStart);
            self_destruct();
        }
    }

    if (ConfigParser::RecognizeQuotedValues && *nextToken == '(') {
        if (strncmp(tokenStart, "parameters", nextToken - tokenStart) == 0)
            type = ConfigParser::FunctionParameters;
        else {
            if (PreviewMode_) {
                char *err = xstrdup(SQUID_ERROR_TOKEN);
                CfgLineTokens_.push(err);
                return err;
            } else {
                debugs(3, DBG_CRITICAL, "FATAL: Unknown cfg function: " << tokenStart);
                self_destruct();
            }
        }
    } else
        type = ConfigParser::SimpleToken;

    char *token = NULL;
    if (nextToken - tokenStart) {
        if (ConfigParser::StrictMode && type == ConfigParser::SimpleToken) {
            bool tokenIsNumber = true;
            for (const char *s = tokenStart; s != nextToken; ++s) {
                const bool isValidChar = isalnum(*s) || strchr(".,()-=_/:", *s) ||
                                         (tokenIsNumber && *s == '%' && (s + 1 == nextToken));

                if (!isdigit(*s))
                    tokenIsNumber = false;

                if (!isValidChar) {
                    if (PreviewMode_) {
                        char *err = xstrdup(SQUID_ERROR_TOKEN);
                        CfgLineTokens_.push(err);
                        return err;
                    } else {
                        debugs(3, DBG_CRITICAL, "FATAL: Not alphanumeric character '"<< *s << "' in unquoted token " << tokenStart);
                        self_destruct();
                    }
                }
            }
        }
        token = xstrndup(tokenStart, nextToken - tokenStart + 1);
        CfgLineTokens_.push(token);
    }

    if (*nextToken != '\0' && *nextToken != '#') {
        ++nextToken;
    }

    return token;
}