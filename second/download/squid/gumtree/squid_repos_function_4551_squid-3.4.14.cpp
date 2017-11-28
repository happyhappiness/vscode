void
aclParseEuiList(SplayNode<Eui::Eui64 *> **curlist)
{
    char *t = NULL;
    SplayNode<Eui::Eui64*> **Top = curlist;
    Eui::Eui64 *q = NULL;

    while ((t = strtokFile())) {
        if ((q = aclParseEuiData(t)) == NULL)
            continue;

        *Top = (*Top)->insert(q, aclEui64Compare);
    }
}