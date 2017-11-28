void
HttpHdrScTarget::mergeWith(const HttpHdrScTarget * new_sc)
{
    assert(new_sc);
    /* Don't touch the target - this is used to get the operations for a
     * single surrogate
     */

    if (new_sc->hasNoStore())
        noStore(true);

    if (new_sc->hasNoStoreRemote())
        noStoreRemote(true);

    if (new_sc->hasMaxAge() && !hasMaxAge()) {
        maxAge(new_sc->maxAge());
        maxStale(new_sc->maxStale());
    }

    if (new_sc->hasContent() && !hasContent())
        Content(new_sc->content());

}