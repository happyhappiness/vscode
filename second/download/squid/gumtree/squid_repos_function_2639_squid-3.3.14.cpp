bool
ConfigOptionVector::parse(char const *option, const char *value, int isaReconfig)
{
    Vector<ConfigOption *>::iterator i = options.begin();

    while (i != options.end()) {
        if ((*i)->parse(option,value, isaReconfig))
            return true;

        ++i;
    }

    return false;
}