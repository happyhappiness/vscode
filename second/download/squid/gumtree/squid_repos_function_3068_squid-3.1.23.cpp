void
CommAcceptCbParams::print(std::ostream &os) const
{
    CommCommonCbParams::print(os);
    if (nfd >= 0)
        os << ", newFD " << nfd;
}