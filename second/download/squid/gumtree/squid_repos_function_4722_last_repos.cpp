std::ostream&
SBuf::print(std::ostream &os) const
{
    os.write(buf(), length());
    ++stats.toStream;
    return os;
}