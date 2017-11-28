void
MemStore::cleanReadable(const sfileno fileno)
{
    Ipc::Mem::PutPage(map->extras(fileno).page);
    theCurrentSize -= Ipc::Mem::PageSize();
}