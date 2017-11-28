bool
ConfigParser::CfgFile::startParse(char *path)
{
    assert(wordFile == NULL);
    debugs(3, 3, "Parsing from " << path);
    if ((wordFile = fopen(path, "r")) == NULL) {
        debugs(3, DBG_CRITICAL, "WARNING: file :" << path << " not found");
        return false;
    }

#if _SQUID_WINDOWS_
    setmode(fileno(wordFile), O_TEXT);
#endif

    filePath = path;
    return getFileLine();
}