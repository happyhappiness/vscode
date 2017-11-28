static void
ProcessMacros(char*& line, int& len)
{
    SubstituteMacro(line, len, "${process_name}", TheKidName);
    SubstituteMacro(line, len, "${process_number}", xitoa(KidIdentifier));
}