static int
aclArpCompare(Eui::Eui48 * const &a, Eui::Eui48 * const &b)
{
    return memcmp(a, b, sizeof(Eui::Eui48));
}