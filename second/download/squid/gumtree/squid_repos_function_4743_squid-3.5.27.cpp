void
ACLEui64::parse()
{
    while (const char * t = strtokFile()) {
        if (Eui::Eui64 * q = aclParseEuiData(t)) {
            eui64Data.insert(*q);
            delete q;
        }
    }
}