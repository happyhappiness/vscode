TextException& TextException::operator=(const TextException &right)
{
    if (this==&right) return *this;
    if (message) xfree(message);
    message=(right.message?xstrdup(right.message):NULL);
    theFileName=right.theFileName;
    theLineNo=right.theLineNo;
    theId=right.theId;
    return *this;
}