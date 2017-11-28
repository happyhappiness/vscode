std::ostream&
MemBlob::dump(std::ostream &os) const
{
    os << "id @" << (void *)this
    << "mem:" << static_cast<void*>(mem)
    << ",capacity:" << capacity
    << ",size:" << size
    << ",refs:" << LockCount() << "; ";
    return os;
}