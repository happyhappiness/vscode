int
CossSwapDir::canStore(StoreEntry const &e)const
{

    /* Check if the object is a special object, we can't cache these */

    if (EBIT_TEST(e.flags, ENTRY_SPECIAL))
        return -1;

    /* Otherwise, we're ok */
    /* Return load, cs->aq.aq_numpending out of MAX_ASYNCOP */
    return io->load();
}