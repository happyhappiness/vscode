int
Auth::Digest::UserRequest::authenticated() const
{
    if (user() != NULL && user()->credentials() == Auth::Ok)
        return 1;

    return 0;
}