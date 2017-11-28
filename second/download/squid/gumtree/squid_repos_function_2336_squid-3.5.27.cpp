void
UpdateRequestNotes(ConnStateData *csd, HttpRequest &request, NotePairs const &helperNotes)
{
    // Tag client connection if the helper responded with clt_conn_tag=tag.
    if (const char *connTag = helperNotes.findFirst("clt_conn_tag")) {
        if (csd)
            csd->connectionTag(connTag);
    }
    if (!request.notes)
        request.notes = new NotePairs;
    request.notes->replaceOrAdd(&helperNotes);
}