NotePairs &
SyncNotes(AccessLogEntry &ale, HttpRequest &request)
{
    // XXX: auth code only has access to HttpRequest being authenticated
    // so we must handle the case where HttpRequest is set without ALE being set.

    if (!ale.notes) {
        if (!request.notes)
            request.notes = new NotePairs;
        ale.notes = request.notes;
    } else {
        assert(ale.notes == request.notes);
    }
    return *ale.notes;
}