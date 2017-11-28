bool set(const char *src, const int len) {
        if (len > SZ_EUI64_BUF) return false;
        if (len < SZ_EUI64_BUF) clear();
        memcpy(eui, src, len);
        return true;
    }