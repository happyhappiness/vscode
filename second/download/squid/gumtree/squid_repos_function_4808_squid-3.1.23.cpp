size_t
authenticateRequestRefCount (AuthUserRequest *aRequest)
{
    return aRequest->refCount();
}