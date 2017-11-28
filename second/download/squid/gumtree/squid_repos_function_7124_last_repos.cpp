void
Ipc::StoreMap::startAppending(const sfileno fileno)
{
    Anchor &s = anchorAt(fileno);
    assert(s.writing());
    s.lock.startAppending();
    debugs(54, 5, "restricted entry " << fileno << " to appending " << path);
}