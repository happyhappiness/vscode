std::ostream&
SBuf::dump(std::ostream &os) const
{
    os << id
       << ": ";
    store_->dump(os);
    os << ", offset:" << off_
       << ", len:" << len_
       << ") : '";
    print(os);
    os << '\'' << std::endl;
    return os;
# if 0
    // alternate implementation, based on Raw() API.
    os << Raw("SBuf", buf(), length()) <<
       ". id: " << id <<
       ", offset:" << off_ <<
       ", len:" << len_ <<
       ", store: ";
    store_->dump(os);
    os << std::endl;
    return os;
#endif
}