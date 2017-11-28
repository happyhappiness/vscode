void
Mgr::Action::run(StoreEntry* entry, bool writeHttpHeader)
{
    debugs(16, 5, HERE);
    collect();
    fillEntry(entry, writeHttpHeader);
}