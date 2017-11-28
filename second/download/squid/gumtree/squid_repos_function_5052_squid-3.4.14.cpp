StoreSearch *
Fs::Ufs::UFSSwapDir::search(String const url, HttpRequest *request)
{
    if (url.size())
        fatal ("Cannot search by url yet\n");

    return new Fs::Ufs::StoreSearchUFS (this);
}