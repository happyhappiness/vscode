const Ipc::StoreMap::Anchor *
Ipc::StoreMap::openForReadingAt(const sfileno fileno)
{
    debugs(54, 5, "opening entry " << fileno << " for reading " << path);
    Anchor &s = anchorAt(fileno);

    if (!s.lock.lockShared()) {
        debugs(54, 5, "cannot open busy entry " << fileno <<
               " for reading " << path);
        return NULL;
    }

    if (s.empty()) {
        s.lock.unlockShared();
        debugs(54, 7, "cannot open empty entry " << fileno <<
               " for reading " << path);
        return NULL;
    }

    if (s.waitingToBeFreed) {
        s.lock.unlockShared();
        debugs(54, 7, "cannot open marked entry " << fileno <<
               " for reading " << path);
        return NULL;
    }

    debugs(54, 5, "opened entry " << fileno << " for reading " << path);
    return &s;
}