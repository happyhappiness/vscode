Auth::Scheme::Pointer
Auth::UserRequest::scheme() const
{
    return Auth::Scheme::Find(user()->config->type());
}