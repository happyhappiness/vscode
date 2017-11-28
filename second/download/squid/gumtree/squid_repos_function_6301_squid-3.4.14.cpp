void
Ipc::Forwarder::callException(const std::exception& e)
{
    try {
        handleException(e);
    } catch (const std::exception& ex) {
        debugs(54, DBG_CRITICAL, HERE << ex.what());
    }
    AsyncJob::callException(e);
}