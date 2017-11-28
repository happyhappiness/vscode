int
ACLUrlStrategy::match (ACLData<char const *> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    char *esc_buf = xstrdup(urlCanonical(checklist->request));
    rfc1738_unescape(esc_buf);
    int result = data->match(esc_buf);
    safe_free(esc_buf);
    return result;
}