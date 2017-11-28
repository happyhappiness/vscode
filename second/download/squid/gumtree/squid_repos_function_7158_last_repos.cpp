void
Ipc::StoreMap::relocate(const sfileno name, const sfileno fileno)
{
    // preserve special meaning for zero; see fileNoByName
    fileNos->items[name] = fileno+1;
}