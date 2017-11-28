void
store_client::fail()
{
    object_ok = false;
    /* synchronous open failures callback from the store,
     * before startSwapin detects the failure.
     * TODO: fix this inconsistent behaviour - probably by
     * having storeSwapInStart become a callback functions,
     * not synchronous
     */

    if (_callback.pending())
        callback(0, true);
}