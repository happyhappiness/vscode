bool
Ipc::StoreMap::openKeyless(Update::Edition &edition)
{
    return visitVictims([&](const sfileno name) {
        Update::Edition temp;
        temp.name = name;
        temp.fileNo = fileNoByName(temp.name);
        if ((temp.anchor = openForWritingAt(temp.fileNo))) {
            debugs(54, 5, "created entry " << temp.fileNo <<
                   " for updating " << path);
            Must(temp);
            edition = temp;
            return true;
        }
        return false;
    });
}