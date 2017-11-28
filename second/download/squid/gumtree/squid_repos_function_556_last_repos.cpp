void
HttpBody::packInto(Packable * p) const
{
    assert(p);

    if (mb->contentSize())
        p->append(mb->content(), mb->contentSize());
}