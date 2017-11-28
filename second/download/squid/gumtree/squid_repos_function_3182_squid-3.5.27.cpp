void
CommTimeoutCbPtrFun::print(std::ostream &os) const
{
    os << '(';
    params.print(os);
    os << ')';
}