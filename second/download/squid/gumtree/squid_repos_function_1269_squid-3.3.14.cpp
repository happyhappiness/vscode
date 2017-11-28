void
EventDialer::print(std::ostream &os) const
{
    os << '(';
    if (theArg)
        os << theArg << (isLockedArg ? "*?" : "");
    os << ')';
}