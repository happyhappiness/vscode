int64_t
ConnStateData::bodySizeLeft()
{
    // XXX: this logic will not work for chunked requests with unknown sizes

    if (bodyPipe != NULL)
        return bodyPipe->unproducedSize();

    return 0;
}