Adaptation::ServicePointer
Adaptation::FindService(const Service::Id& key)
{
    typedef Services::iterator SI;
    for (SI i = AllServices().begin(); i != AllServices().end(); ++i) {
        if ((*i)->cfg().key == key)
            return *i;
    }
    return NULL;
}