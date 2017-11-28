static const char *
debugLogKid(void)
{
    if (KidIdentifier != 0) {
        static char buf[16];
        if (!*buf) // optimization: fill only once after KidIdentifier is set
            snprintf(buf, sizeof(buf), " kid%d", KidIdentifier);
        return buf;
    }

    return "";
}