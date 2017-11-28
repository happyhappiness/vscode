void
Rock::IoState::write(char const *buf, size_t size, off_t coreOff, FREE *dtor)
{
    // TODO: move to create?
    if (!coreOff) {
        assert(theBuf.isNull());
        assert(payloadEnd <= slotSize);
        theBuf.init(min(payloadEnd, slotSize), slotSize);
        // start with our header; TODO: consider making it a trailer
        DbCellHeader header;
        assert(static_cast<int64_t>(sizeof(header)) <= payloadEnd);
        header.payloadSize = payloadEnd - sizeof(header);
        theBuf.append(reinterpret_cast<const char*>(&header), sizeof(header));
    } else {
        // Core uses -1 offset as "append". Sigh.
        assert(coreOff == -1);
        assert(!theBuf.isNull());
    }

    theBuf.append(buf, size);
    offset_ += size; // so that Core thinks we wrote it

    if (dtor)
        (dtor)(const_cast<char*>(buf)); // cast due to a broken API?
}