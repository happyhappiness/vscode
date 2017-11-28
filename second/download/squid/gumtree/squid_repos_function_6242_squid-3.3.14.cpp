Kid& Kids::get(size_t i)
{
    assert(i < count());
    return storage[i];
}