sfileno
FileMap::allocate(sfileno suggestion)
{
    int word;

    if (suggestion >= capacity_)
        suggestion = 0;

    if (!testBit(suggestion))
        return suggestion;

    word = suggestion >> LONG_BIT_SHIFT;

    for (unsigned int count = 0; count < nwords; ++count) {
        if (bitmap[word] != ALL_ONES)
            break;

        word = (word + 1) % nwords;
    }

    for (unsigned char bit = 0; bit < BITS_IN_A_LONG; ++bit) {
        suggestion = ((unsigned long) word << LONG_BIT_SHIFT) | bit;

        if (!testBit(suggestion)) {
            return suggestion;
        }
    }

    grow();
    return allocate(capacity_ >> 1);
}