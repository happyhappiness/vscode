char *
ConfigParser::Undo()
{
    static char undoToken[CONFIG_LINE_LIMIT];
    if (!Undo_.empty()) {
        xstrncpy(undoToken, Undo_.front().c_str(), sizeof(undoToken));
        undoToken[sizeof(undoToken) - 1] = '\0';
        if (!PreviewMode_)
            Undo_.pop();
        return undoToken;
    }
    return NULL;
}