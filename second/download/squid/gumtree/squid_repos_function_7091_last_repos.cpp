void
Ipc::Inquirer::callException(const std::exception& e)
{
    debugs(54, 3, HERE);
    try {
        handleException(e);
    } catch (const std::exception& ex) {
        debugs(54, DBG_CRITICAL, HERE << ex.what());
    }
    AsyncJob::callException(e);
}