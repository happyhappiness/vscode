void
clientReplyContext::forgetHit()
{
    StoreEntry *e = http->storeEntry();
    assert(e); // or we are not dealing with a hit
    // We probably have not locked the entry earlier, unfortunately. We lock it
    // now so that we can unlock two lines later (and trigger cleanup).
    // Ideally, ClientHttpRequest::storeEntry() should lock/unlock, but it is
    // used so inconsistently that simply adding locking there leads to bugs.
    e->lock("clientReplyContext::forgetHit");
    http->storeEntry(NULL);
    e->unlock("clientReplyContext::forgetHit"); // may delete e
}