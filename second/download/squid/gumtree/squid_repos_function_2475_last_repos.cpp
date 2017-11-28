void
StoreEntry::setReleaseFlag()
{
    if (EBIT_TEST(flags, RELEASE_REQUEST))
        return;

    debugs(20, 3, "StoreEntry::setReleaseFlag: '" << getMD5Text() << "'");

    EBIT_SET(flags, RELEASE_REQUEST);

    Store::Root().markForUnlink(*this);
}