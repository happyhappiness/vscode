int
ACLUrlLoginStrategy::match(ACLData<char const *> * &data, ACLFilledChecklist *checklist)
{
    if (checklist->request->url.userInfo().isEmpty()) {
        debugs(28, 5, "URL has no user-info details. cannot match");
        return 0; // nothing can match
    }

    static char str[MAX_URL]; // should be big enough for a single URI segment

    const SBuf::size_type len = checklist->request->url.userInfo().copy(str, sizeof(str)-1);
    str[len] = '\0';
    rfc1738_unescape(str);
    return data->match(str);
}