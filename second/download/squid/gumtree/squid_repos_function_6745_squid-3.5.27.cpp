bool
Eui::Eui64::decode(const char *asc)
{
    if (eui64_aton(asc, (struct eui64 *)eui) != 0) {
        debugs(28, 4, "id=" << (void*)this << " decode fail on " << asc);
        return false;
    }

    debugs(28, 4, "id=" << (void*)this << " ATON decoded " << asc);
    return true;
}