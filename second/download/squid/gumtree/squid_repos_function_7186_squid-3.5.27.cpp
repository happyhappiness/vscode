void
Mgr::Inquirer::sendResponse()
{
    if (!strands.empty() && aggrAction->aggregatable()) {
        removeCloseHandler();
        AsyncJob::Start(new ActionWriter(aggrAction, conn));
        conn = NULL; // should not close because we passed it to ActionWriter
    }
}