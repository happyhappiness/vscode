int
AIODiskIOStrategy::load()
{
    return aq.aq_numpending * 1000 / MAX_ASYNCOP;
}