uint64_t BodyPipe::unproducedSize() const
{
    return bodySize() - thePutSize; // bodySize() asserts that size is known
}