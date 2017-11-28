char const *
Auth::UserRequest::denyMessage(char const * const default_message)
{
    if (getDenyMessage() == NULL)
        return default_message;

    return getDenyMessage();
}