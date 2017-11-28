void
HttpBody::packInto(Packer * p) const
{
    assert(p);

    if (mb->contentSize())
        packerAppend(p, mb->content(), mb->contentSize());
}