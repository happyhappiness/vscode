Note::Pointer
Notes::add(const String &noteKey)
{
    typedef Notes::NotesList::iterator AMLI;
    for (AMLI i = notes.begin(); i != notes.end(); ++i) {
        if ((*i)->key == noteKey)
            return (*i);
    }

    Note::Pointer note = new Note(noteKey);
    notes.push_back(note);
    return note;
}