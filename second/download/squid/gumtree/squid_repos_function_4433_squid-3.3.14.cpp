void
aclParseArpList(SplayNode<Eui::Eui48 *> **curlist)
{
    char *t = NULL;
    SplayNode<Eui::Eui48*> **Top = curlist;
    Eui::Eui48 *q = NULL;

    while ((t = strtokFile())) {
        if ((q = aclParseArpData(t)) == NULL)
            continue;

        *Top = (*Top)->insert(q, aclArpCompare);
    }
}