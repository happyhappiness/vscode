void
CommCommonCbParams::print(std::ostream &os) const
{
    if (conn != NULL)
        os << conn;
    else
        os << "FD " << fd;

    if (xerrno)
        os << ", errno=" << xerrno;
    if (flag != Comm::OK)
        os << ", flag=" << flag;
    if (data)
        os << ", data=" << data;
}