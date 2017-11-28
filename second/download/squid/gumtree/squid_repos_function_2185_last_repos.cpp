bool
ConfigParser::CfgFile::getFileLine()
{
    // Else get the next line
    if (fgets(parseBuffer, CONFIG_LINE_LIMIT, wordFile) == NULL) {
        /* stop reading from file */
        fclose(wordFile);
        wordFile = NULL;
        parseBuffer[0] = '\0';
        return false;
    }
    parsePos = parseBuffer;
    currentLine = parseBuffer;
    lineNo++;
    return true;
}