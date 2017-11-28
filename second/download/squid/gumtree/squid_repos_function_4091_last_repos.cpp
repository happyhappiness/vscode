int
ACLUrlStrategy::match (ACLData<char const *> * &data, ACLFilledChecklist *checklist)
{
    char *esc_buf = SBufToCstring(checklist->request->effectiveRequestUri());
    rfc1738_unescape(esc_buf);
    int result = data->match(esc_buf);
    xfree(esc_buf);
    return result;
}