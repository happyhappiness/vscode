void Adaptation::Icap::Options::cfgIntHeader(const HttpHeader *h, const char *fname, int &value)
{
    const String s = h->getByName(fname);

    if (s.size() && xisdigit(*s.termedBuf()))
        value = atoi(s.termedBuf());
    else
        value = -1;

    debugs(93,5, HERE << "int header: " << fname << ": " << value);
}