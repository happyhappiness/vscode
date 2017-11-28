void
Mgr::StoreToCommWriter::Abort(void* param)
{
    StoreToCommWriter* mgrWriter = static_cast<StoreToCommWriter*>(param);
    if (Comm::IsConnOpen(mgrWriter->clientConnection))
        mgrWriter->clientConnection->close();
}