void
Mgr::Filler::swanSong()
{
    debugs(16, 5, HERE);
    action->sendResponse(requestId);
    StoreToCommWriter::swanSong();
}