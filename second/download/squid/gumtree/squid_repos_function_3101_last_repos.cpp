std::ostream &
operator <<(std::ostream &os, const ConnStateData::PinnedIdleContext &pic)
{
    return os << pic.connection << ", request=" << pic.request;
}