virtual bool parse(const char *buf, int len, bool eof) {
        if (len)
            textBuf.append(buf, len);
        return true;
    }