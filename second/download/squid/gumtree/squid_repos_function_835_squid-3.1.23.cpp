void
httpBodyPackInto(const HttpBody * body, Packer * p)
{
    assert(body && p);

    if (body->mb->contentSize())
        packerAppend(p, body->mb->content(), body->mb->contentSize());
}