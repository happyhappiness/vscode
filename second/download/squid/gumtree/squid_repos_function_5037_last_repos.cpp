size_t
Rock::IoState::writeToBuffer(char const *buf, size_t size)
{
    // do not buffer a cell header for nothing
    if (!size)
        return 0;

    if (!theBuf.size) {
        // will fill the header in writeToDisk when the next slot is known
        theBuf.appended(sizeof(DbCellHeader));
    }

    size_t forCurrentSlot = min(size, static_cast<size_t>(theBuf.spaceSize()));
    theBuf.append(buf, forCurrentSlot);
    offset_ += forCurrentSlot; // so that Core thinks we wrote it
    return forCurrentSlot;
}