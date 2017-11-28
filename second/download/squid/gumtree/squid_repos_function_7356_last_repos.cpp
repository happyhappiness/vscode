void
Mgr::ActionWriter::start()
{
    debugs(16, 5, HERE);
    Must(action != NULL);

    StoreToCommWriter::start();
    action->fillEntry(entry, false);
}