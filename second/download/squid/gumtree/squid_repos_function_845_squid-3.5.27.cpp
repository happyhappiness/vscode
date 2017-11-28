void
DelayVector::Id::bytesIn(int qty)
{
    iterator pos = ids.begin();

    while (pos != ids.end()) {
        (*pos)->bytesIn(qty);
        ++pos;
    }

    theVector->kickReads();
}