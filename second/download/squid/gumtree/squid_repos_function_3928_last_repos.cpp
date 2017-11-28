int Ssl::ErrorDetail::convert(const char *code, const char **value) const
{
    *value = "-";
    for (int i=0; ErrorFormatingCodes[i].code!=NULL; ++i) {
        const int len = strlen(ErrorFormatingCodes[i].code);
        if (strncmp(code,ErrorFormatingCodes[i].code, len)==0) {
            ErrorDetail::fmt_action_t action  = ErrorFormatingCodes[i].fmt_action;
            *value = (this->*action)();
            return len;
        }
    }
    return 0;
}