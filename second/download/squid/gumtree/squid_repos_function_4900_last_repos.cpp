static const CharacterSet &
LineCharacters()
{
    static const CharacterSet line = CharacterSet::LF.complement("non-LF");
    return line;
}