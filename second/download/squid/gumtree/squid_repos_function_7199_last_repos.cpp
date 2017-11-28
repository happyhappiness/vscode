bool
Ipc::MemMapSlot::empty() const
{
    for (unsigned char const*u = key; u < key + sizeof(key); ++u) {
        if (*u)
            return false;
    }
    return true;
}