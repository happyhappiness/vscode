void
DownloaderContext::finished()
{
    delete http;
    http = nullptr;
}