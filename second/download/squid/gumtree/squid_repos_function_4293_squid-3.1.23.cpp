int
ACLMyPortNameStrategy::match(ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    if (checklist->conn() != NULL)
        return data->match(checklist->conn()->port->name);
    if (checklist->request != NULL)
        return data->match(checklist->request->myportname.termedBuf());
    return 0;
}