template <class Key, class Value>
unsigned int
VectorMap<Key,Value>::insert (Key const key)
{
    unsigned char index = findKeyIndex (key);
    assert (!indexUsed(index));

    key_map[index] = key;

    ++nextMapPosition;

    return index;
}