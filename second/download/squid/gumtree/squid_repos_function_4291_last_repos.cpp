bool
ACLNoteStrategy::matchNotes(ACLData<MatchType> *noteData, const NotePairs *note) const
{
    for (auto &entry: note->entries) {
        if (!delimiters.value.isEmpty()) {
            NotePairs::Entry e(entry->name.termedBuf(), "");
            Parser::Tokenizer t(StringToSBuf(entry->value));
            SBuf s;
            while (t.token(s, delimiters.value)) {
                e.value = s.c_str();
                if (noteData->match(&e))
                    return true;
            }
            s = t.remaining();
            e.value = s.c_str();
            if (noteData->match(&e))
                return true;
        }
        if (noteData->match(entry))
            return true;
    }
    return false;
}