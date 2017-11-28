template <class Key, class Value>
unsigned int
VectorMap<Key,Value>::size() const
{
    return nextMapPosition;
}