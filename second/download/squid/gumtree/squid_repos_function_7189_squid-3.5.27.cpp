void
Mgr::Filler::start()
{
    debugs(16, 5, HERE);
    Must(requestId != 0);
    Must(action != NULL);

    StoreToCommWriter::start();
    action->run(entry, false);
}