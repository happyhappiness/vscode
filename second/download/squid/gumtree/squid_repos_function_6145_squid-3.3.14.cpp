bool
Eui::Eui64::decode(const char *asc)
{
    if (eui64_aton(asc, (struct eui64 *)eui) != 0) return false;

    return true;
}