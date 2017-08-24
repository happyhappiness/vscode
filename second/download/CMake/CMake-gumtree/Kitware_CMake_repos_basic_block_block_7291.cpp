r(n = 0; beg < end; n += 3)
        snprintf(buf + n, 4, "%02x:", *(const unsigned char *) beg++)