String &
String::operator =(char const *aString)
{
    reset(aString);
    return *this;
}