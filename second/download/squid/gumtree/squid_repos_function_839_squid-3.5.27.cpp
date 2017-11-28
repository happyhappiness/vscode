void
DelayVector::parse()
{
    iterator pos = pools.begin();

    while (pos != pools.end()) {
        (*pos)->parse();
        ++pos;
    }
}