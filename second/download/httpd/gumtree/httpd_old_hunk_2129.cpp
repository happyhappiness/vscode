
            if (current->token.type == TOKEN_NOT) {
                current->value = !current->value;
            }
            break;

        case TOKEN_RE:
            if (!error) {
                error = "No operator before regex in expr \"%s\" in file %s";
            }
        case TOKEN_LBRACE:
            if (!error) {
