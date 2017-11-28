StoreSearch *
UFSSwapDir::search(String const url, HttpRequest *request)
{
    if (url.size())
        fatal ("Cannot search by url yet\n");

    return new StoreSearchUFS (this);
}