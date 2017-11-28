void
Mgr::StoreToCommWriter::NoteStoreCopied(void* data, StoreIOBuffer ioBuf)
{
    Must(data != NULL);
    // make sync Store call async to get async call protections and features
    StoreToCommWriter* writer = static_cast<StoreToCommWriter*>(data);
    typedef UnaryMemFunT<StoreToCommWriter, StoreIOBuffer> MyDialer;
    AsyncCall::Pointer call =
        asyncCall(16, 5, "Mgr::StoreToCommWriter::noteStoreCopied",
                  MyDialer(writer, &StoreToCommWriter::noteStoreCopied, ioBuf));
    ScheduleCallHere(call);
}