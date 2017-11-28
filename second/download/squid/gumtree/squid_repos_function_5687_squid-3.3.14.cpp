IpcIoPendingRequest *
IpcIoFile::dequeueRequest(const unsigned int requestId)
{
    Must(requestId != 0);

    RequestMap *map = NULL;
    RequestMap::iterator i = requestMap1.find(requestId);

    if (i != requestMap1.end())
        map = &requestMap1;
    else {
        i = requestMap2.find(requestId);
        if (i != requestMap2.end())
            map = &requestMap2;
    }

    if (!map) // not found in both maps
        return NULL;

    IpcIoPendingRequest *pending = i->second;
    map->erase(i);
    return pending;
}