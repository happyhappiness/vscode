int
responseFinishedOrFailed(HttpReply * rep, StoreIOBuffer const & receivedData)
{
    if (rep == NULL && receivedData.data == NULL && receivedData.length == 0)
        return 1;

    return 0;
}