void
CommIoCbPtrFun::print(std::ostream &os) const
{
    os << '(';
    params.print(os);
    os << ')';
}