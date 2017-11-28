SBuf&
SBuf::lowAppend(const char * memArea, size_type areaSize)
{
    rawSpace(areaSize); //called method also checks n <= maxSize()
    store_->append(memArea, areaSize);
    len_ += areaSize;
    ++stats.append;
    return *this;
}