void Adaptation::Icap::ModXact::decideWritingAfterPreview(const char *kind)
{
    if (preview.ieof()) // nothing more to write
        stopWriting(true);
    else if (state.parsing == State::psIcapHeader) // did not get a reply yet
        state.writing = State::writingPaused; // wait for the ICAP server reply
    else
        stopWriting(true); // ICAP server reply implies no post-preview writing

    debugs(93, 6, HERE << "decided on writing after " << kind << " preview" <<
           status());
}