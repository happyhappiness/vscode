int
ACLUrlPathStrategy::match (ACLData<char const *> * &data, ACLFilledChecklist *checklist)
{
    char *esc_buf = xstrdup(checklist->request->urlpath.termedBuf());
    rfc1738_unescape(esc_buf);
    int result = data->match(esc_buf);
    safe_free(esc_buf);
    return result;
}