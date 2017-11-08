const char * ZEXPORT zError(err)
    int err;
{
    return ERR_MSG(err);
}