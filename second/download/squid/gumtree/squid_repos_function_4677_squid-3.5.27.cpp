bool
ACLNoteData::match(HttpRequest *request)
{
    if (request->notes != NULL && matchNotes(request->notes.getRaw()))
        return true;
#if USE_ADAPTATION
    const Adaptation::History::Pointer ah = request->adaptLogHistory();
    if (ah != NULL && ah->metaHeaders != NULL && matchNotes(ah->metaHeaders.getRaw()))
        return true;
#endif
    return false;
}