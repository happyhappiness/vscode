void
Adaptation::Config::removeService(const String& service)
{
    removeRule(service);
    const Groups& groups = AllGroups();
    for (unsigned int i = 0; i < groups.size(); ) {
        const ServiceGroupPointer group = groups[i];
        const ServiceGroup::Store& services = group->services;
        typedef ServiceGroup::Store::const_iterator SGSI;
        for (SGSI it = services.begin(); it != services.end(); ++it) {
            if (*it == service) {
                group->removedServices.push_back(service);
                ServiceGroup::Store::iterator newend;
                newend = std::remove(group->services.begin(), group->services.end(), service);
                group->services.resize(newend-group->services.begin());
                debugs(93, 5, "adaptation service " << service <<
                       " removed from group " << group->id);
                break;
            }
        }
        if (services.empty()) {
            removeRule(group->id);
            Groups::iterator newend;
            newend = std::remove(AllGroups().begin(), AllGroups().end(), group);
            AllGroups().resize(newend-AllGroups().begin());
        } else {
            ++i;
        }
    }
}