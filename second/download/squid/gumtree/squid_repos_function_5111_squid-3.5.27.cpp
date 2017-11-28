const char *
Http::StatusLine::reason() const
{
    return reason_ ? reason_ : Http::StatusCodeString(status());
}