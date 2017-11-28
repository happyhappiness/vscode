sfileno
Ipc::StoreMap::fileNoByName(const sfileno name) const
{
    // fileNos->items are initialized to zero, which we treat as "name is fileno";
    // a positive value means the entry anchor got moved to a new fileNo
    if (const int item = fileNos->items[name])
        return item-1;
    return name;
}