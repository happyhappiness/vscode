Kid* Kids::find(pid_t pid)
{
    assert(pid > 0);
    assert(count() > 0);

    for (size_t i = 0; i < storage.size(); ++i) {
        if (storage[i].getPid() == pid)
            return &storage[i];
    }
    return NULL;
}