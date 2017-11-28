void
StoreController::allowCollapsing(StoreEntry *e, const RequestFlags &reqFlags,
                                 const HttpRequestMethod &reqMethod)
{
    const KeyScope keyScope = reqFlags.refresh ? ksRevalidation : ksDefault;
    e->makePublic(keyScope); // this is needed for both local and SMP collapsing
    if (transients)
        transients->startWriting(e, reqFlags, reqMethod);
    debugs(20, 3, "may " << (transients && e->mem_obj->xitTable.index >= 0 ?
                             "SMP-" : "locally-") << "collapse " << *e);
}