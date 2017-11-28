void
Client::serverComplete2()
{
    debugs(11,5,HERE << "serverComplete2 " << this);

#if USE_ADAPTATION
    if (virginBodyDestination != NULL)
        stopProducingFor(virginBodyDestination, true);

    if (!doneWithAdaptation())
        return;
#endif

    completeForwarding();
}