StoreSearch *
StoreController::search(String const url, HttpRequest *request)
{
    /* cheat, for now you can't search the memory hot cache */
    return swapDir->search(url, request);
}