void
String::append(String const &old)
{
    append(old.rawBuf(), old.len_);
}