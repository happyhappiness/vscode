bool Kids::someSignaled(const int sgnl) const
{
    for (size_t i = 0; i < storage.size(); ++i) {
        if (storage[i].signaled(sgnl))
            return true;
    }
    return false;
}