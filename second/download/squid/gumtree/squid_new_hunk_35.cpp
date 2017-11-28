                          SQUIDSTRINGPRINT(cfg.key),
                          cfg.methodStr(), cfg.vectPointStr(), cfg.bypass,
                          SQUIDSTRINGPRINT(cfg.uri));
    }
}

bool
Adaptation::Config::finalize()
{
    if (!onoff) {
        clear();
        return false;
    }

    // create service reps from service configs
    int created = 0;

    typedef ServiceConfigs::const_iterator VISCI;
    const ServiceConfigs &configs = serviceConfigs;
    for (VISCI i = configs.begin(); i != configs.end(); ++i) {
        const ServiceConfigPointer cfg = *i;
        if (FindService(cfg->key) != NULL) {
            debugs(93,0, "ERROR: Duplicate adaptation service name: " <<
                   cfg->key);
            continue; // TODO: make fatal
        }
        ServicePointer s = createService(cfg);
        if (s != NULL) {
            AllServices().push_back(s);
            created++;
        }
    }

    debugs(93,3, HERE << "Created " << created << " adaptation services");

    // services remember their configs; we do not have to
    serviceConfigs.clean();
    return true;
}

// poor man for_each
template <class Collection>
static void
FinalizeEach(Collection &collection, const char *label)
