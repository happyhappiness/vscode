ACLData<HttpRequest *> *
ACLNoteData::clone() const
{
    ACLNoteData * result = new ACLNoteData;
    result->values = values->clone();
    result->name = name;
    return result;
}