char *
hex_utf_char(struct main_args *margs, int flag)
{
    int ival, ichar;
    int iUTF2, iUTF3, iUTF4;

    char *up = (flag ? margs->ulist : margs->tlist);
    if (!up)
        return NULL;

    char *upd = strrchr(up, '@');
    size_t a = (upd ? (size_t)(upd - up) : strlen(up) );

    char *ul = (char *) xmalloc(strlen(up)+1);
    size_t n = 0;
    int nl = 0;
    iUTF2 = 0;
    iUTF3 = 0;
    iUTF4 = 0;

    while (n < strlen(up)) {
        if (flag && n == a)
            break;
        if (up[n] == '@') {
            ul[nl] = '@';
            ++nl;
            ++n;
            continue;
        }
        ival = up[n];
        if (ival > 64 && ival < 71)
            ichar = (ival - 55) * 16;
        else if (ival > 96 && ival < 103)
            ichar = (ival - 87) * 16;
        else if (ival > 47 && ival < 58)
            ichar = (ival - 48) * 16;
        else {
            debug((char *) "%s| %s: WARNING: Invalid Hex value %c\n", LogTime(), PROGRAM, ival);
            xfree(ul);
            return NULL;
        }

        if (n == a - 1) {
            debug((char *) "%s| %s: WARNING: Invalid Hex UTF-8 string %s\n", LogTime(), PROGRAM, up);
            xfree(ul);
            return NULL;
        }
        ++n;
        ival = up[n];
        if (ival > 64 && ival < 71)
            ichar = ichar + ival - 55;
        else if (ival > 96 && ival < 103)
            ichar = ichar + ival - 87;
        else if (ival > 47 && ival < 58)
            ichar = ichar + ival - 48;
        else {
            debug((char *) "%s| %s: WARNING: Invalid Hex value %c\n", LogTime(), PROGRAM, ival);
            xfree(ul);
            return NULL;
        }

        if (iUTF2) {
            if (iUTF2 == 0xC2 && ichar > 0x7F && ichar < 0xC0) {
                iUTF2 = 0;
                ul[nl - 1] = (char)ichar;
            } else if (iUTF2 == 0xC3 && ichar > 0x7F && ichar < 0xC0) {
                iUTF2 = 0;
                ul[nl - 1] = (char)(ichar + 64);
            } else if (iUTF2 > 0xC3 && iUTF2 < 0xE0 && ichar > 0x7F && ichar < 0xC0) {
                iUTF2 = 0;
                ul[nl] = (char)ichar;
                ++nl;
            } else {
                iUTF2 = 0;
                ul[nl] = (char)ichar;
                ul[nl + 1] = '\0';
                debug((char *) "%s| %s: WARNING: Invalid UTF-8 sequence for Unicode %s\n", LogTime(), PROGRAM, ul);
                xfree(ul);
                return NULL;
            }
        } else if (iUTF3) {
            if (iUTF3 == 0xE0 && ichar > 0x9F && ichar < 0xC0) {
                iUTF3 = 1;
                ul[nl] = (char)ichar;
                ++nl;
            } else if (iUTF3 > 0xE0 && iUTF3 < 0xED && ichar > 0x7F && ichar < 0xC0) {
                iUTF3 = 2;
                ul[nl] = (char)ichar;
                ++nl;
            } else if (iUTF3 == 0xED && ichar > 0x7F && ichar < 0xA0) {
                iUTF3 = 3;
                ul[nl] = (char)ichar;
                ++nl;
            } else if (iUTF3 > 0xED && iUTF3 < 0xF0 && ichar > 0x7F && ichar < 0xC0) {
                iUTF3 = 4;
                ul[nl] = (char)ichar;
                ++nl;
            } else if (iUTF3 > 0 && iUTF3 < 5 && ichar > 0x7F && ichar < 0xC0) {
                iUTF3 = 0;
                ul[nl] = (char)ichar;
                ++nl;
            } else {
                iUTF3 = 0;
                ul[nl] = (char)ichar;
                ul[nl + 1] = '\0';
                debug((char *) "%s| %s: WARNING: Invalid UTF-8 sequence for Unicode %s\n", LogTime(), PROGRAM, ul);
                xfree(ul);
                return NULL;
            }
        } else if (iUTF4) {
            if (iUTF4 == 0xF0 && ichar > 0x8F && ichar < 0xC0) {
                iUTF4 = 1;
                ul[nl] = (char)ichar;
                ++nl;
            } else if (iUTF4 > 0xF0 && iUTF3 < 0xF4 && ichar > 0x7F && ichar < 0xC0) {
                iUTF4 = 2;
                ul[nl] = (char)ichar;
                ++nl;
            } else if (iUTF4 == 0xF4 && ichar > 0x7F && ichar < 0x90) {
                iUTF4 = 3;
                ul[nl] = (char)ichar;
                ++nl;
            } else if (iUTF4 > 0 && iUTF4 < 5 && ichar > 0x7F && ichar < 0xC0) {
                if (iUTF4 == 4)
                    iUTF4 = 0;
                else
                    iUTF4 = 4;
                ul[nl] = (char)ichar;
                ++nl;
            } else {
                iUTF4 = 0;
                ul[nl] = (char)ichar;
                ul[nl + 1] = '\0';
                debug((char *) "%s| %s: WARNING: Invalid UTF-8 sequence for Unicode %s\n", LogTime(), PROGRAM, ul);
                xfree(ul);
                return NULL;
            }
        } else if (ichar < 0x80) {
            /* UTF1 */
            ul[nl] = (char)ichar;
            ++nl;
        } else if (ichar > 0xC1 && ichar < 0xE0) {
            /* UTF2 (Latin) */
            iUTF2 = ichar;
            ul[nl] = (char)ichar;
            ++nl;
        } else if (ichar > 0xDF && ichar < 0xF0) {
            /* UTF3 */
            iUTF3 = ichar;
            ul[nl] = (char)ichar;
            ++nl;
        } else if (ichar > 0xEF && ichar < 0xF5) {
            /* UTF4 */
            iUTF4 = ichar;
            ul[nl] = (char)ichar;
            ++nl;
        } else {
            ul[nl] = (char)ichar;
            ul[nl + 1] = '\0';
            debug((char *) "%s| %s: WARNING: Invalid UTF-8 sequence for Unicode %s\n", LogTime(), PROGRAM, ul);
            xfree(ul);
            return NULL;
        }
        ++n;
    }

    ul[nl] = '\0';
    if (iUTF2 || iUTF3 || iUTF4) {
        debug((char *) "%s| %s: INFO: iUTF2: %d iUTF3: %d iUTF4: %d\n", LogTime(), PROGRAM, iUTF2, iUTF3, iUTF4);
        debug((char *) "%s| %s: WARNING: Invalid UTF-8 sequence for Unicode %s\n", LogTime(), PROGRAM, ul);
        xfree(ul);
        return NULL;
    }
    if (flag && upd)
        ul = strcat(ul, upd);
    return ul;
}