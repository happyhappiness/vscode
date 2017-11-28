void
PconnPool::closeN(int n)
{
    hash_table *hid = table;
    hash_first(hid);

    // close N connections, one per list, to treat all lists "fairly"
    for (int i = 0; i < n && count(); ++i) {

        hash_link *current = hash_next(hid);
        if (!current) {
            hash_first(hid);
            current = hash_next(hid);
            Must(current); // must have one because the count() was positive
        }

        // may delete current
        reinterpret_cast<IdleConnList*>(current)->closeN(1);
    }
}