void
CossState::close()
{
    debugs(79, 3, "storeCossClose: offset " << swap_filen);

    StoreFScoss::GetInstance().stats.close.ops++;
    StoreFScoss::GetInstance().stats.close.success++;
    SD->storeCossMemBufUnlock(this);
    doCallback(0);
}