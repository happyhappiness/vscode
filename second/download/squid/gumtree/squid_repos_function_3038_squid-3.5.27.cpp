void
StoreEntry::touch()
{
    lastref = squid_curtime;
    Store::Root().reference(*this);
}