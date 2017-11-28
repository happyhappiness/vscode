ACLData<NotePairs::Entry *> *
ACLNoteData::clone() const
{
    ACLNoteData * result = new ACLNoteData;
    result->values = dynamic_cast<ACLStringData*>(values->clone());
    assert(result->values);
    result->name = name;
    return result;
}