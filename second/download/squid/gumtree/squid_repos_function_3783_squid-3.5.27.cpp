char *
UrnState::getHost (String &urlpath)
{
    char * result;
    size_t p;

    /** FIXME: this appears to be parsing the URL. *very* badly. */
    /*   a proper encapsulated URI/URL type needs to clear this up. */
    if ((p=urlpath.find(':')) != String::npos) {
        result=xstrndup(urlpath.rawBuf(),p-1);
    } else {
        result = xstrndup(urlpath.rawBuf(),urlpath.size());
    }
    return result;
}