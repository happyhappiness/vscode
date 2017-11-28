void ServerStateData::cleanAdaptation()
{
    debugs(11,5, HERE << "cleaning ICAP; ACL: " << adaptationAccessCheckPending);

    if (virginBodyDestination != NULL)
        stopProducingFor(virginBodyDestination, false);

    announceInitiatorAbort(adaptedHeadSource);

    if (adaptedBodySource != NULL)
        stopConsumingFrom(adaptedBodySource);

    if (!adaptationAccessCheckPending) // we cannot cancel a pending callback
        assert(doneWithAdaptation()); // make sure the two methods are in sync
}