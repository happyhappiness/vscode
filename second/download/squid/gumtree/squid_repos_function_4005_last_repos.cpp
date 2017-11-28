void
ACLARP::parse()
{
    while (const char *t = ConfigParser::strtokFile()) {
        if (Eui::Eui48 *q = aclParseArpData(t)) {
            aclArpData.insert(*q);
            delete q;
        }
    }
}