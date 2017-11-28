int
ACLProxyAuth::matchForCache(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);
    assert (checklist->auth_user_request);
    return data->match(checklist->auth_user_request->username());
}