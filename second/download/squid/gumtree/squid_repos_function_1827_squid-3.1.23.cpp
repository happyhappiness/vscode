static bool
isDefined(const std::string &name)
{
    if (!name.size())
        return true;

    for (int i = 0; defines[i].name; i++) {
        if (name.compare(defines[i].name) == 0)
            return defines[i].defined;
    }

    return false;
}