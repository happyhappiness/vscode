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