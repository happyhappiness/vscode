    void finalizeMsg(const char *msg, const String &culprit, bool error) const;

public:
    String kind;
    Id id;
    Store services;

    Method method; /// based on the first added service
    VectPoint point; /// based on the first added service

    const bool allServicesSame; // whether we can freely substitute services
};
