void
AuthUserRequest::setDenyMessage (char const *aString)
{
    safe_free (message);
    message = xstrdup (aString);
}