void
BodyPipe::clearProducer(bool atEof)
{
    if (theProducer.set()) {
        debugs(91,7, HERE << "clearing BodyPipe producer" << status());
        theProducer.clear();
        if (atEof) {
            if (!bodySizeKnown())
                theBodySize = thePutSize;
            else if (bodySize() != thePutSize)
                debugs(91,3, HERE << "aborting on premature eof" << status());
        } else {
            // asserta that we can detect the abort if the consumer joins later
            assert(!bodySizeKnown() || bodySize() != thePutSize);
        }
        scheduleBodyEndNotification();
    }
}