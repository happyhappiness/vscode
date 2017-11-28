String &
String::operator =(String const &old)
{
    clean(); // TODO: optimize to avoid cleaning the buffer we can use
    if (old.size() > 0)
        allocAndFill(old.rawBuf(), old.size());
    return *this;
}