void
Rock::Rebuild::swanSong()
{
    debugs(47,3, HERE << "cache_dir #" << sd->index << " rebuild level: " <<
           StoreController::store_dirs_rebuilding);
    --StoreController::store_dirs_rebuilding;
    storeRebuildComplete(&counts);
}