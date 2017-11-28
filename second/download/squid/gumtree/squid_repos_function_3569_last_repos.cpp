void Adaptation::Icap::ModXact::finishNullOrEmptyBodyPreview(MemBuf &)
{
    Must(!virginBodyWriting.active()); // one reason we handle it here
    Must(!virgin.body_pipe);          // another reason we handle it here
    Must(!preview.ad());

    // do not add last-chunk because our Encapsulated header says null-body
    // addLastRequestChunk(buf);
    preview.wrote(0, true);

    Must(preview.done());
    Must(preview.ieof());
}