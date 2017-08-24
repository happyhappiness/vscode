e(*ptr && (ISALPHA(*ptr) || ISXDIGIT(*ptr) || (*ptr == '-') ||
                     (*ptr == '.') || (*ptr == '_') || (*ptr == '~')))
        ptr++