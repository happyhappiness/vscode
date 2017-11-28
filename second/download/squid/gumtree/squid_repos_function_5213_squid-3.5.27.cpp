void
Rock::IoState::tryWrite(char const *buf, size_t size, off_t coreOff)
{
    debugs(79, 7, swap_filen << " writes " << size << " more");

    // either this is the first write or append; we do not support write gaps
    assert(!coreOff || coreOff == -1);

    // allocate the first slice during the first write
    if (!coreOff) {
        assert(sidCurrent < 0);
        sidCurrent = reserveSlotForWriting(); // throws on failures
        assert(sidCurrent >= 0);
        writeAnchor().start = sidCurrent;
    }

    // buffer incoming data in slot buffer and write overflowing or final slots
    // quit when no data left or we stopped writing on reentrant error
    while (size > 0 && theFile != NULL) {
        assert(sidCurrent >= 0);
        const size_t processed = writeToBuffer(buf, size);
        buf += processed;
        size -= processed;
        const bool overflow = size > 0;

        // We do not write a full buffer without overflow because
        // we would not yet know what to set the nextSlot to.
        if (overflow) {
            const SlotId sidNext = reserveSlotForWriting(); // throws
            assert(sidNext >= 0);
            writeToDisk(sidNext);
        } else if (Store::Root().transientReaders(*e)) {
            // write partial buffer for all remote hit readers to see
            writeBufToDisk(-1, false);
        }
    }

}