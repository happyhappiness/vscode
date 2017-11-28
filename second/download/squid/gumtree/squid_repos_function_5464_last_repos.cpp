void
memPoolIterateDone(MemPoolIterator ** iter)
{
    assert(iter != NULL);
    Iterator.pool = NULL;
    *iter = NULL;
}