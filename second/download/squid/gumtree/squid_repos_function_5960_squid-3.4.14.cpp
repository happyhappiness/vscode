void
Snmp::Session::free()
{
    if (community_len > 0) {
        Must(community != NULL);
        xfree(community);
    }
    if (peername != NULL)
        xfree(peername);
    clear();
}