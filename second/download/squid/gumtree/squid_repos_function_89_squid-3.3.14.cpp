std::ostream &operator << (std::ostream &aStream, StreamTest &anObject)
{
    return anObject.serialise(aStream);
}