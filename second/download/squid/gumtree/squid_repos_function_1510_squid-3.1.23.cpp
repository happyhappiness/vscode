void
DelayPools::deregisterForUpdates (Updateable *anObject)
{
    Vector<Updateable *>::iterator pos = toUpdate.begin();

    while (pos != toUpdate.end() && *pos != anObject) {
        ++pos;
    }

    if (pos != toUpdate.end()) {
        /* move all objects down one */
        Vector<Updateable *>::iterator temp = pos;
        ++pos;

        while (pos != toUpdate.end()) {
            *temp = *pos;
            ++temp;
            ++pos;
        }

        toUpdate.pop_back();
    }
}