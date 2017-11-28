bool
Adaptation::Ecap::ServiceConfig::grokExtension(const char *name, const char *value)
{
    extensions.push_back(std::make_pair(name, value));
    return true;
}