template <class Key, class Value>
bool
VectorMap<Key,Value>::indexUsed (unsigned char const index) const
{
    return index < size();
}