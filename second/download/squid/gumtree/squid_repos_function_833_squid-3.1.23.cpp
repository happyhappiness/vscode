void
httpBodyClean(HttpBody * body)
{
    assert(body);

    if (!body->mb->isNull())
        body->mb->clean();

    delete body->mb;

    body->mb = NULL;
}