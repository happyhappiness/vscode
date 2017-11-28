void
CommCommonCbParams::print(std::ostream &os) const
{
    os << "FD " << fd;
    if (xerrno)
        os << ", errno=" << xerrno;
    if (flag != COMM_OK)
        os << ", flag=" << flag;
    if (data)
        os << ", data=" << data;
}