static const char *
gen_quote_escape(const std::string &var)
{
    static std::string esc;
    esc.clear();

    for (int i = 0; i < var.length(); ++i) {
        switch (var[i]) {
        case '"':
        case '\\':
            esc += '\\';
        default:
            esc += var[i];
        }
    }

    return esc.c_str();
}