bool
String::operator != (String const &that) const
{
    if (0 == this->cmp(that))
        return false;

    return true;
}