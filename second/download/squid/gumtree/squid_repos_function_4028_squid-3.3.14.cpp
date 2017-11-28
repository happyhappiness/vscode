void Adaptation::Icap::ModXact::virginConsume()
{
    debugs(93, 9, HERE << "consumption guards: " << !virgin.body_pipe << isRetriable <<
           isRepeatable << canStartBypass << protectGroupBypass);

    if (!virgin.body_pipe)
        return; // nothing to consume

    if (isRetriable)
        return; // do not consume if we may have to retry later

    BodyPipe &bp = *virgin.body_pipe;
    const bool wantToPostpone = isRepeatable || canStartBypass || protectGroupBypass;

    // Why > 2? HttpState does not use the last bytes in the buffer
    // because delayAwareRead() is arguably broken. See
    // HttpStateData::maybeReadVirginBody for more details.
    if (wantToPostpone && bp.buf().spaceSize() > 2) {
        // Postponing may increase memory footprint and slow the HTTP side
        // down. Not postponing may increase the number of ICAP errors
        // if the ICAP service fails. We may also use "potential" space to
        // postpone more aggressively. Should the trade-off be configurable?
        debugs(93, 8, HERE << "postponing consumption from " << bp.status());
        return;
    }

    const size_t have = static_cast<size_t>(bp.buf().contentSize());
    const uint64_t end = virginConsumed + have;
    uint64_t offset = end;

    debugs(93, 9, HERE << "max virgin consumption offset=" << offset <<
           " acts " << virginBodyWriting.active() << virginBodySending.active() <<
           " consumed=" << virginConsumed <<
           " from " << virgin.body_pipe->status());

    if (virginBodyWriting.active())
        offset = min(virginBodyWriting.offset(), offset);

    if (virginBodySending.active())
        offset = min(virginBodySending.offset(), offset);

    Must(virginConsumed <= offset && offset <= end);

    if (const size_t size = static_cast<size_t>(offset - virginConsumed)) {
        debugs(93, 8, HERE << "consuming " << size << " out of " << have <<
               " virgin body bytes");
        bp.consume(size);
        virginConsumed += size;
        Must(!isRetriable); // or we should not be consuming
        disableRepeats("consumed content");
        disableBypass("consumed content", true);
    }
}