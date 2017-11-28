static int
aclEui64Compare(Eui::Eui64 * const &a, Eui::Eui64 * const &b)
{
    return memcmp(a, b, sizeof(Eui::Eui64));
}