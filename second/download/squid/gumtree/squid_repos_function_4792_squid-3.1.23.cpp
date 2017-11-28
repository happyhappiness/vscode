int
ACLProxyAuth::match(ACLChecklist *checklist)
{
    int ti;

    if ((ti = AuthenticateAcl(checklist)) != 1)
        return ti;

    ti = matchProxyAuth(checklist);

    return ti;
}