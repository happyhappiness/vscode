std::ostream &
SwapChecksum24::print(std::ostream &os) const
{
    return os << raw[0] << '-' << raw[1] << '-' << raw[2];
}