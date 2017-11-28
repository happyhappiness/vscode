bool
ACLNoteData::matchNotes(NotePairs *note)
{
    if (note == NULL)
        return false;

    debugs(28, 3, "Checking " << name);

    if (values->empty())
        return (note->findFirst(name.termedBuf()) != NULL);

    for (std::vector<NotePairs::Entry *>::iterator i = note->entries.begin(); i!= note->entries.end(); ++i) {
        if ((*i)->name.cmp(name.termedBuf()) == 0) {
            if (values->match((*i)->value.termedBuf()))
                return true;
        }
    }
    return false;
}