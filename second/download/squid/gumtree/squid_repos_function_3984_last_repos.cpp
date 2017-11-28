int
ACLUrlPathStrategy::match (ACLData<char const *> * &data, ACLFilledChecklist *checklist)
{
    if (checklist->request->url.path().isEmpty())
        return -1;

    char *esc_buf = SBufToCstring(checklist->request->url.path());
    rfc1738_unescape(esc_buf);
    int result = data->match(esc_buf);
    xfree(esc_buf);
    return result;
}