void
ACLARP::parse()
{
    while (const char *t = strtokFile()) {
        if (Eui::Eui48 *q = aclParseArpData(t)) {
            aclArpData.insert(*q);
            delete q;
        }
    }
}