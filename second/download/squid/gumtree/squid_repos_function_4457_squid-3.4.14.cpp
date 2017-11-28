int
ACLUrlPathStrategy::match (ACLData<char const *> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    if (!checklist->request->urlpath.size())
        return -1;

    char *esc_buf = xstrdup(checklist->request->urlpath.termedBuf());
    rfc1738_unescape(esc_buf);
    int result = data->match(esc_buf);
    safe_free(esc_buf);
    return result;
}