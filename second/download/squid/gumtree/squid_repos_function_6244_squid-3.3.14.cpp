bool Kids::allExitedHappy() const
{
    for (size_t i = 0; i < storage.size(); ++i) {
        if (!storage[i].exitedHappy())
            return false;
    }
    return true;
}