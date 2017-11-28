int
ACLNoteStrategy::match(ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    if (const auto request = checklist->request) {
        if (request->notes != NULL && matchNotes(data, request->notes.getRaw()))
            return 1;
#if USE_ADAPTATION
        const Adaptation::History::Pointer ah = request->adaptLogHistory();
        if (ah != NULL && ah->metaHeaders != NULL && matchNotes(data, ah->metaHeaders.getRaw()))
            return 1;
#endif
    }
    return 0;
}