void
CharacterSet::printChars(std::ostream &os) const
{
    for (size_t idx = 0; idx < 256; ++idx) {
        if (chars_[idx])
            os << static_cast<char>(idx);
    }
}