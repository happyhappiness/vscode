bool
HttpStateData::doneWithServer() const
{
    return fd < 0;
}