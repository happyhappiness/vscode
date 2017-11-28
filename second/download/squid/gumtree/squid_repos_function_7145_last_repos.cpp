bool
Ipc::StoreMap::visitVictims(const NameFilter visitor)
{
    // Hopefully, we find a usable entry much sooner (TODO: use time?).
    // The min() will protect us from division by zero inside the loop.
    const int searchLimit = min(10000, entryLimit());
    int tries = 0;
    for (; tries < searchLimit; ++tries) {
        const sfileno name = static_cast<sfileno>(++anchors->victim % entryLimit());
        if (visitor(name))
            return true;
    }

    debugs(54, 5, "no victims found in " << path << "; tried: " << tries);
    return false;
}