void
ServerStateData::haveParsedReplyHeaders()
{
    Must(theFinalReply);
    maybePurgeOthers();

    // adaptation may overwrite old offset computed using the virgin response
    const bool partial = theFinalReply->content_range &&
                         theFinalReply->sline.status() == Http::scPartialContent;
    currentOffset = partial ? theFinalReply->content_range->spec.offset : 0;
}