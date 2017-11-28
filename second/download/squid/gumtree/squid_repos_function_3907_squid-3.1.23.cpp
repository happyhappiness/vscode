void Adaptation::Icap::ModXact::callException(const std::exception &e)
{
    if (!canStartBypass || isRetriable) {
        Adaptation::Icap::Xaction::callException(e);
        return;
    }

    try {
        debugs(93, 3, HERE << "bypassing " << inCall << " exception: " <<
               e.what() << ' ' << status());
        bypassFailure();
    } catch (const std::exception &bypassE) {
        Adaptation::Icap::Xaction::callException(bypassE);
    }
}