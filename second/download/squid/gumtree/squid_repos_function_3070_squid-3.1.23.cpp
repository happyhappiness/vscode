void
CommConnectCbParams::print(std::ostream &os) const
{
    CommCommonCbParams::print(os);
    os << ", " << dns;
}