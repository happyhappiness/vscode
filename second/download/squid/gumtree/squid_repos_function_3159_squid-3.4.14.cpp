void
FdeCbPtrFun::print(std::ostream &os) const
{
    os << '(';
    params.print(os);
    os << ')';
}