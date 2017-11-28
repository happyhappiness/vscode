void
ConnStateData::startShutdown()
{
    // RegisteredRunner API callback - Squid has been shut down

    // if connection is idle terminate it now,
    // otherwise wait for grace period to end
    if (pipeline.empty())
        endingShutdown();
}