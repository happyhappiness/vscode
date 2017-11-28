void
StoreEntry::deferProducer(const AsyncCall::Pointer &producer)
{
    if (!deferredProducer)
        deferredProducer = producer;
    else
        debugs(20, 5, HERE << "Deferred producer call is allready set to: " <<
               *deferredProducer << ", requested call: " << *producer);
}