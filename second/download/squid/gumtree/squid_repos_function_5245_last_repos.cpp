size_t
Client::calcBufferSpaceToReserve(size_t space, const size_t wantSpace) const
{
    if (space < wantSpace) {
        const size_t maxSpace = SBuf::maxSize; // absolute best
        space = min(wantSpace, maxSpace); // do not promise more than asked
    }

#if USE_ADAPTATION
    if (responseBodyBuffer) {
        return 0;   // Stop reading if already overflowed waiting for ICAP to catch up
    }

    if (virginBodyDestination != NULL) {
        /*
         * BodyPipe buffer has a finite size limit.  We
         * should not read more data from the network than will fit
         * into the pipe buffer or we _lose_ what did not fit if
         * the response ends sooner that BodyPipe frees up space:
         * There is no code to keep pumping data into the pipe once
         * response ends and serverComplete() is called.
         */
        const size_t adaptor_space = virginBodyDestination->buf().potentialSpaceSize();

        debugs(11,9, "Client may read up to min(" <<
               adaptor_space << ", " << space << ") bytes");

        if (adaptor_space < space)
            space = adaptor_space;
    }
#endif

    return space;
}