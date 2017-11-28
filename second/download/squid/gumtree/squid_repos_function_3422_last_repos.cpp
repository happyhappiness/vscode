void
Adaptation::Ecap::ServiceRep::finalize()
{
    Adaptation::Service::finalize();
    if (!cfg().connectionEncryption.configured())
        writeableCfg().connectionEncryption.defaultTo(true);
    theService = FindAdapterService(cfg().uri);
    if (theService) {
        try {
            tryConfigureAndStart();
            Must(up());
        } catch (const std::exception &e) { // standardized exceptions
            if (!handleFinalizeFailure(e.what()))
                throw; // rethrow for upper layers to handle
        } catch (...) { // all other exceptions
            if (!handleFinalizeFailure("unrecognized exception"))
                throw; // rethrow for upper layers to handle
        }
        return; // success or handled exception
    } else {
        debugs(93,DBG_IMPORTANT, "WARNING: configured ecap_service was not loaded: " << cfg().uri);
    }
}