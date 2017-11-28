    // We do not lock e because we do not want to prevent its destruction;
    // e is tied to us via mem_obj so we will know when it is destructed.
    locals->at(index) = e;
    return e;
}

StoreEntry *
Transients::findCollapsed(const sfileno index)
{
    if (!map)
        return NULL;

