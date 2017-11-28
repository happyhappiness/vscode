AuthUser *
AuthDigestUserRequest::authUser() const
{
    return const_cast<AuthUser *>(user());
}