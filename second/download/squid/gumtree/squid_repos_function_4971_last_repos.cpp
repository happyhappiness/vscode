void
Rock::SwapDir::maintain()
{
    // The Store calls this to free some db space, but there is nothing wrong
    // with a full() db, except when db has to shrink after reconfigure, and
    // we do not support shrinking yet (it would have to purge specific slots).
    // TODO: Disable maintain() requests when they are pointless.
}