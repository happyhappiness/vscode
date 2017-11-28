const char *TextException::what() const throw()
{
    /// \todo add file:lineno
    return message ? message : "TextException without a message";
}