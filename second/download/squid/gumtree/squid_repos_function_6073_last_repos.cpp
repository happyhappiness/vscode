CharacterSet
operator- (CharacterSet lhs, const CharacterSet &rhs)
{
    lhs -= rhs;
    return lhs;
}