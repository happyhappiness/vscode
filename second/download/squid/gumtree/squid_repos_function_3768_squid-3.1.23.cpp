void
Adaptation::Config::finalize()
{
    // create service reps from service configs
    typedef Vector<ServiceConfig*>::const_iterator VISCI;
    const Vector<ServiceConfig*> &configs = serviceConfigs;
    debugs(93,3, HERE << "Found " << configs.size() << " service configs.");
    for (VISCI i = configs.begin(); i != configs.end(); ++i) {
        const ServiceConfig &cfg = **i;
        if (FindService(cfg.key) != NULL) {
            debugs(93,0, "ERROR: Duplicate adaptation service name: " <<
                   cfg.key);
            continue; // TODO: make fatal
        }
        ServicePointer s = createService(**i);
        if (s != NULL)
            AllServices().push_back(s);
    }

    debugs(93,3, HERE << "Created " << configs.size() <<
           " message adaptation services.");
}