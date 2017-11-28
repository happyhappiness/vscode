{
    safe_free(message);
    message = xstrdup(aString);
}

char const *
Auth::UserRequest::getDenyMessage() const
{
    return message;
}

char const *
Auth::UserRequest::denyMessage(char const * const default_message) const
{
    if (getDenyMessage() == NULL)
        return default_message;

    return getDenyMessage();
}
