void
CossSwapDir::unlink(StoreEntry & e)
{
    debugs(79, 3, "storeCossUnlink: offset " << e.swap_filen);
    StoreFScoss::GetInstance().stats.unlink.ops++;
    StoreFScoss::GetInstance().stats.unlink.success++;
    storeCossRemove(this, &e);
}