char *
ConfigParser::StripComment(char *token)
{
    if (!token)
        return NULL;

    // we are outside the quoted string context
    // assume that anything starting with a '#' is a comment
    if (char *comment = strchr(token, '#')) {
        *comment = '\0'; // remove the comment from this token
        (void)strtok(NULL, ""); // remove the comment from the current line
        if (!*token)
            return NULL; // token was a comment
    }

    return token;
}