int
ACLExtUser::match(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);
    if (checklist->request->extacl_user.size()) {
        return data->match(checklist->request->extacl_user.termedBuf());
    } else {
        return -1;
    }
}