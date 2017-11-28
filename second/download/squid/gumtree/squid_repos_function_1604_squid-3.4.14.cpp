template <class Key, class Value>
unsigned char
VectorMap<Key,Value>::findKeyIndex (Key const key) const
{
    for (unsigned int index = 0; index < size(); ++index) {
        assert(indexUsed(index));

        if (key_map[index] == key)
            return index;
    }

    /* not in map */
    return size();
}