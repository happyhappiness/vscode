bool BodyPipe::exhausted() const
{
    return !expectMoreAfter(theGetSize);
}