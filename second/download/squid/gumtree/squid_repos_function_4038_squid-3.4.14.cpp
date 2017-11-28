void Adaptation::Icap::ModXact::writePreviewBody()
{
    debugs(93, 8, HERE << "will write Preview body from " <<
           virgin.body_pipe << status());
    Must(state.writing == State::writingPreview);
    Must(virgin.body_pipe != NULL);

    const size_t sizeMax = (size_t)virgin.body_pipe->buf().contentSize();
    const size_t size = min(preview.debt(), sizeMax);
    writeSomeBody("preview body", size);

    // change state once preview is written

    if (preview.done())
        decideWritingAfterPreview("body");
}