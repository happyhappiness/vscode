std::ostream &
Dns::LookupDetails::print(std::ostream &os) const
{
    if (wait > 0)
        os << "lookup_wait=" << wait;
    if (error.size())
        os << " lookup_err=" << error;
    return os;
}