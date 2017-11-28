uint64_t BodyPipe::bodySize() const
{
    assert(bodySizeKnown());
    return static_cast<uint64_t>(theBodySize);
}