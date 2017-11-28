void
httpBodySet(HttpBody * body, MemBuf * mb)
{
    assert(body);
    assert(body->mb->isNull());
    delete body->mb;
    body->mb = mb;		/* absorb */
}