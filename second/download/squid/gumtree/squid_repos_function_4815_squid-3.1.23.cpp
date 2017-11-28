char const *
AuthUserRequest::denyMessage(char const * const default_message)
{
    if (this == NULL || getDenyMessage() == NULL) {
        return default_message;
    }

    return getDenyMessage();
}