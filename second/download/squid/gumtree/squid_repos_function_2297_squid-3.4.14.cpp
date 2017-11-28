size_t ServerStateData::replyBodySpace(const MemBuf &readBuf,
                                       const size_t minSpace) const
{
    size_t space = readBuf.spaceSize(); // available space w/o heroic measures
    if (space < minSpace) {
        const size_t maxSpace = readBuf.potentialSpaceSize(); // absolute best
        space = min(minSpace, maxSpace); // do not promise more than asked
    }

#if USE_ADAPTATION
    if (responseBodyBuffer) {
        return 0;	// Stop reading if already overflowed waiting for ICAP to catch up
    }

    if (virginBodyDestination != NULL) {
        /*
         * BodyPipe buffer has a finite size limit.  We
         * should not read more data from the network than will fit
         * into the pipe buffer or we _lose_ what did not fit if
         * the response ends sooner that BodyPipe frees up space:
         * There is no code to keep pumping data into the pipe once
         * response ends and serverComplete() is called.
         *
         * If the pipe is totally full, don't register the read handler.
         * The BodyPipe will call our noteMoreBodySpaceAvailable() method
         * when it has free space again.
         */
        size_t adaptation_space =
            virginBodyDestination->buf().potentialSpaceSize();

        debugs(11,9, "ServerStateData may read up to min(" <<
               adaptation_space << ", " << space << ") bytes");

        if (adaptation_space < space)
            space = adaptation_space;
    }
#endif

    return space;
}