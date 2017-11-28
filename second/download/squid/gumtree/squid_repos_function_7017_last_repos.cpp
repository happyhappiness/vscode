bool Kids::shouldRestartSome() const
{
    for (size_t i = 0; i < storage.size(); ++i) {
        if (storage[i].shouldRestart())
            return true;
    }
    return false;
}