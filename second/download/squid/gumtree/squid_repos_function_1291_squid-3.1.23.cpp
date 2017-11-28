String
String::substr(String::size_type from, String::size_type to) const
{
//    Must(from >= 0 && from < size());
    Must(from < size());
    Must(to > 0 && to <= size());
    Must(to > from);

    String rv;
    rv.limitInit(rawBuf()+from,to-from);
    return rv;
}