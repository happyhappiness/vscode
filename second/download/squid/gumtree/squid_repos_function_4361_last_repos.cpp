static std::string
ldap_escape_value(const std::string &src)
{
    std::stringstream str;
    for (const auto &c : src) {
        switch (c) {
        case '*':
        case '(':
        case ')':
        case '\\':
            str << '\\' << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(c);
            break;
        default:
            str << c;
        }
    }
    return str.str();
}