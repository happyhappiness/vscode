std::ostream &
operator <<(std::ostream &os, const Acl::Options &options)
{
    for (const auto pos: options) {
        assert(pos.second);
        const auto &option = *pos.second;
        if (option.configured())
            os << pos.first << option;
    }
    // TODO: Remember "--" presence and print that delimiter when present.
    // Detecting its need is difficult because parameter flags start with "-".
    return os;
}