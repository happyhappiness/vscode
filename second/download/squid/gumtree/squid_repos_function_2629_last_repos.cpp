virtual bool parse(const char *buf, int len, bool) {
        if (len)
            textBuf.append(buf, len);
        return true;
    }