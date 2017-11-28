void
CommIoCbParams::print(std::ostream &os) const
{
    CommCommonCbParams::print(os);
    if (buf) {
        os << ", size=" << size;
        os << ", buf=" << (void*)buf;
    }
}