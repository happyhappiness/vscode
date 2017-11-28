void
Adaptation::DynamicGroupCfg::add(const String &item)
{
    if (services.empty()) { // first item
        id = item;
    } else {
        id.append(',');
        id.append(item);
    }
    services.push_back(item);
}