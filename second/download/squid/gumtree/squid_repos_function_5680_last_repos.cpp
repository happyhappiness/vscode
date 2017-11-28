void
CredentialsCache::Cleanup(void *data)
{
    debugs(29, 5, "checkpoint");
    // data is this in disguise
    CredentialsCache *self = static_cast<CredentialsCache *>(data);
    self->cleanup();
}