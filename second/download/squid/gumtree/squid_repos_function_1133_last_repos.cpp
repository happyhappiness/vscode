void
Downloader::start()
{
    if (!buildRequest())
        callBack(Http::scInternalServerError);
}