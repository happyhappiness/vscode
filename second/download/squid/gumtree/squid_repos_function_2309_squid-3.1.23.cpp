void
accessLogFreeLogFormat(logformat_token ** tokens)
{
    while (*tokens) {
        logformat_token *token = *tokens;
        *tokens = token->next;
        safe_free(token->data.string);
        xfree(token);
    }
}