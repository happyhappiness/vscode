int
String::psize() const
{
    Must(size() < INT_MAX);
    return size();
}