bool
Parser::Tokenizer::int64(int64_t & result, int base)
{
    if (buf_.isEmpty())
        return false;

    //fixme: account for buf_.size()
    bool neg = false;
    const char *s = buf_.rawContent();
    const char *end = buf_.rawContent() + buf_.length();

    if (*s == '-') {
        neg = true;
        ++s;
    } else if (*s == '+') {
        ++s;
    }

    if (s >= end) return false;
    if (( base == 0 || base == 16) && *s == '0' && (s+1 < end ) &&
            tolower(*(s+1)) == 'x') {
        s += 2;
        base = 16;
    }
    if (base == 0) {
        if ( *s == '0') {
            base = 8;
            ++s;
        } else {
            base = 10;
        }
    }
    if (s >= end) return false;

    uint64_t cutoff;

    cutoff = neg ? -static_cast<uint64_t>(INT64_MIN) : INT64_MAX;
    const int cutlim = cutoff % static_cast<int64_t>(base);
    cutoff /= static_cast<uint64_t>(base);

    int any = 0, c;
    int64_t acc = 0;
    do {
        c = *s;
        if (xisdigit(c)) {
            c -= '0';
        } else if (xisalpha(c)) {
            c -= xisupper(c) ? 'A' - 10 : 'a' - 10;
        } else {
            break;
        }
        if (c >= base)
            break;
        if (any < 0 || static_cast<uint64_t>(acc) > cutoff || (static_cast<uint64_t>(acc) == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    } while (++s < end);

    if (any == 0) // nothing was parsed
        return false;
    if (any < 0) {
        acc = neg ? INT64_MIN : INT64_MAX;
        errno = ERANGE;
        return false;
    } else if (neg)
        acc = -acc;

    result = acc;
    return success(s - buf_.rawContent());
}