bool
Log::TcpLogger::canFit(const size_t len) const
{
    // TODO: limit reporting frequency in addition to reporting only changes

    if (bufferedSize+len <= bufferCapacity) {
        if (drops) {
            // We can get here if a shorter record accidentally fits after we
            // started dropping records. When that happens, the following
            // DBG_IMPORTANT message will mislead admin into thinking that
            // the problem was resolved (for a brief period of time, until
            // another record comes in and overflows the buffer). It is
            // difficult to prevent this without also creating the opposite
            // problem: A huge record that does not fit and is dropped blocks
            // subsequent regular records from being buffered until we write.
            debugs(MY_DEBUG_SECTION, DBG_IMPORTANT, "tcp:" << remote <<
                   " logger stops dropping records after " << drops << " drops" <<
                   "; current buffer use: " << (bufferedSize+len) <<
                   " out of " << bufferCapacity << " bytes");
        }
        return true;
    }

    if (!drops || dieOnError) {
        debugs(MY_DEBUG_SECTION,
               dieOnError ? DBG_CRITICAL : DBG_IMPORTANT,
               "tcp:" << remote << " logger " << bufferCapacity << "-byte " <<
               "buffer overflowed; cannot fit " <<
               (bufferedSize+len-bufferCapacity) << " bytes");
    }

    if (dieOnError)
        fatal("tcp logger buffer overflowed");

    if (!drops) {
        debugs(MY_DEBUG_SECTION, DBG_IMPORTANT, "tcp:" << remote <<
               " logger starts dropping records.");
    }

    return false;
}