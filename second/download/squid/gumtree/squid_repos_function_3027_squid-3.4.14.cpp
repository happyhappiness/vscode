void

StoreEntry::lock()
{
    ++lock_count;
    debugs(20, 3, "StoreEntry::lock: key '" << getMD5Text() <<"' count=" <<
           lock_count  );
    lastref = squid_curtime;
    Store::Root().reference(*this);
}