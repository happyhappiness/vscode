int
UFSSwapDir::canStore(StoreEntry const &e)const
{
    if (IO->shedLoad())
        return -1;

    return IO->load();
}