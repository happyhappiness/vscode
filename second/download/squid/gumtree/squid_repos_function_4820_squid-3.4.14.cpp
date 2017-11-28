void
StoreFScoss::setup()
{
    assert(!initialised);

    coss_index_pool = memPoolCreate("COSS index data", sizeof(CossIndexNode));
    initialised = true;
}