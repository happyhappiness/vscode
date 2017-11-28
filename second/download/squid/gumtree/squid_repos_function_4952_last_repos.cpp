void
Rock::SwapDir::rebuild()
{
    //++StoreController::store_dirs_rebuilding; // see Rock::SwapDir::init()
    AsyncJob::Start(new Rebuild(this));
}