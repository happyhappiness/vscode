bool Kids::allHopeless() const
{
    for (size_t i = 0; i < storage.size(); ++i) {
        if (!storage[i].hopeless())
            return false;
    }
    return true;
}