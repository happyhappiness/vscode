static void
ProcessMacros(char*& line, int& len)
{
    SubstituteMacro(line, len, "${service_name}", service_name.c_str());
    SubstituteMacro(line, len, "${process_name}", TheKidName);
    SubstituteMacro(line, len, "${process_number}", xitoa(KidIdentifier));
}