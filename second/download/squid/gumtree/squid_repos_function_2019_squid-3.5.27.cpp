static const char *
available_if(const std::string &name)
{
    assert(name.size());

    for (int i = 0; defines[i].name; ++i) {
        if (name.compare(defines[i].name) == 0)
            return defines[i].enable;
    }

    return name.c_str();
}