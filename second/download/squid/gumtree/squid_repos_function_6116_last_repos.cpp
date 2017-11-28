RegexPattern &
RegexPattern::operator =(RegexPattern &&o)
{
    flags = std::move(o.flags);
    regex = std::move(o.regex);
    memset(&o.regex, 0, sizeof(o.regex));
    pattern = std::move(o.pattern);
    o.pattern = nullptr;
    return *this;
}