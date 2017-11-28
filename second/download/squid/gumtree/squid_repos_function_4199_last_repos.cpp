const SBuf &
Acl::OptionExtractor::value() const
{
    Must(hasValue);
    return value_;
}