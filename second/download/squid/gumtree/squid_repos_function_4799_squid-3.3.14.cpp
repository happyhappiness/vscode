StoreSearch *
CossSwapDir::search(String const url, HttpRequest *)
{
    if (url.size())
        fatal ("Cannot search by url yet\n");

    return new StoreSearchCoss (this);
}