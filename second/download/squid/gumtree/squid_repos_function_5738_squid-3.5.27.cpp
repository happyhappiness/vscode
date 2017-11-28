int
ACLProxyAuth::matchForCache(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);
    assert (checklist->auth_user_request != NULL);
    return data->match(checklist->auth_user_request->username());
}