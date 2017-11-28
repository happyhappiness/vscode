        file = strwordtok(NULL, &saveptr);
    }
#endif /* HAVE_GLOB */
    return error_count;
}

static void
ReplaceSubstr(char*& str, int& len, unsigned substrIdx, unsigned substrLen, const char* newSubstr)
{
    assert(str != NULL);
    assert(newSubstr != NULL);

    unsigned newSubstrLen = strlen(newSubstr);
    if (newSubstrLen > substrLen)
        str = (char*)realloc(str, len - substrLen + newSubstrLen + 1);

    // move tail part including zero
    memmove(str + substrIdx + newSubstrLen, str + substrIdx + substrLen, len - substrIdx - substrLen + 1);
    // copy new substring in place
    memcpy(str + substrIdx, newSubstr, newSubstrLen);

    len = strlen(str);
}

static void
SubstituteMacro(char*& line, int& len, const char* macroName, const char* substStr)
{
    assert(line != NULL);
    assert(macroName != NULL);
    assert(substStr != NULL);
    unsigned macroNameLen = strlen(macroName);
    while (const char* macroPos = strstr(line, macroName)) // we would replace all occurrences
        ReplaceSubstr(line, len, macroPos - line, macroNameLen, substStr);
}

static void
ProcessMacros(char*& line, int& len)
{
    SubstituteMacro(line, len, "${process_name}", TheKidName);
    SubstituteMacro(line, len, "${process_number}", xitoa(KidIdentifier));
}

static void
trim_trailing_ws(char* str)
{
    assert(str != NULL);
    unsigned i = strlen(str);
    while ((i > 0) && xisspace(str[i - 1]))
        --i;
    str[i] = '\0';
}

static const char*
FindStatement(const char* line, const char* statement)
{
    assert(line != NULL);
    assert(statement != NULL);

    const char* str = skip_ws(line);
    unsigned len = strlen(statement);
    if (strncmp(str, statement, len) == 0) {
        str += len;
        if (*str == '\0')
            return str;
        else if (xisspace(*str))
            return skip_ws(str);
    }

    return NULL;
}

static bool
StrToInt(const char* str, long& number)
{
    assert(str != NULL);

    char* end;
    number = strtol(str, &end, 0);

    return (end != str) && (*end == '\0'); // returns true if string contains nothing except number
}

static bool
EvalBoolExpr(const char* expr)
{
    assert(expr != NULL);
    if (strcmp(expr, "true") == 0) {
        return true;
    } else if (strcmp(expr, "false") == 0) {
        return false;
    } else if (const char* equation = strchr(expr, '=')) {
        const char* rvalue = skip_ws(equation + 1);
        char* lvalue = (char*)xmalloc(equation - expr + 1);
        xstrncpy(lvalue, expr, equation - expr + 1);
        trim_trailing_ws(lvalue);

        long number1;
        if (!StrToInt(lvalue, number1))
            fatalf("String is not a integer number: '%s'\n", lvalue);
        long number2;
        if (!StrToInt(rvalue, number2))
            fatalf("String is not a integer number: '%s'\n", rvalue);

        xfree(lvalue);
        return number1 == number2;
    }
    fatalf("Unable to evaluate expression '%s'\n", expr);
    return false; // this place cannot be reached
}

static int
parseOneConfigFile(const char *file_name, unsigned int depth)
{
    FILE *fp = NULL;
    const char *orig_cfg_filename = cfg_filename;
    const int orig_config_lineno = config_lineno;
