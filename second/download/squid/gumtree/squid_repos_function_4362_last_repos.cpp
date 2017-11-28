static bool
build_filter(std::string &filter, const char *templ, const char *user, const char *group)
{
    std::stringstream str;
    while (*templ) {
        switch (*templ) {
        case '%':
            ++templ;
            switch (*templ) {
            case 'u':
            case 'v':
                ++templ;
                str << ldap_escape_value(user);
                break;
            case 'g':
            case 'a':
                ++templ;
                str << ldap_escape_value(group);
                break;
            default:
                fprintf(stderr, "ERROR: Unknown filter template string %%%c\n", *templ);
                filter = str.str();
                return false;
            }
            break;
        case '\\':
            ++templ;
            if (*templ) {
                str << *templ;
                ++templ;
            }
            break;
        default:
            str << *templ;
            ++templ;
            break;
        }
    }
    filter = str.str();
    return true;
}