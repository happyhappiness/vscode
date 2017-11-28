void Adaptation::Icap::ModXact::callException(const std::exception &e)
{
    if (!canStartBypass || isRetriable) {
        if (!isRetriable) {
            if (const TextException *te = dynamic_cast<const TextException *>(&e))
                detailError(ERR_DETAIL_EXCEPTION_START + te->id());
            else
                detailError(ERR_DETAIL_EXCEPTION_OTHER);
        }
        Adaptation::Icap::Xaction::callException(e);
        return;
    }

    try {
        debugs(93, 3, HERE << "bypassing " << inCall << " exception: " <<
               e.what() << ' ' << status());
        bypassFailure();
    } catch (const TextException &bypassTe) {
        detailError(ERR_DETAIL_EXCEPTION_START + bypassTe.id());
        Adaptation::Icap::Xaction::callException(bypassTe);
    } catch (const std::exception &bypassE) {
        detailError(ERR_DETAIL_EXCEPTION_OTHER);
        Adaptation::Icap::Xaction::callException(bypassE);
    }
}