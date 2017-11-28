void
SBuf::setAt(size_type pos, char toset)
{
    checkAccessBounds(pos);
    cow();
    store_->mem[off_+pos] = toset;
    ++stats.setChar;
}