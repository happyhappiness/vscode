void
ACLMethodData::parse()
{
    while (char *t = ConfigParser::strtokFile()) {
        HttpRequestMethod m;
        m.HttpRequestMethodXXX(t);
        values.push_back(m);
        if (values.back() == Http::METHOD_PURGE)
            ++ThePurgeCount; // configuration code wants to know
    }
}