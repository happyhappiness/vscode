bool Kids::someRunning() const
{
    for (size_t i = 0; i < storage.size(); ++i) {
        if (storage[i].running())
            return true;
    }
    return false;
}