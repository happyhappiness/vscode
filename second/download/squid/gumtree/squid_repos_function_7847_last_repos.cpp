void
strupper(char *s)
{
    while (*s) {
#if UNUSED_CODE
#if !defined(KANJI_WIN95_COMPATIBILITY)
        if (lp_client_code_page() == KANJI_CODEPAGE) {

            if (is_shift_jis(*s)) {
                if (is_sj_lower(s[0], s[1]))
                    s[1] = sj_toupper2(s[1]);
                s += 2;
            } else if (is_kana(*s)) {
                s++;
            } else {
                if (islower((int)(unsigned char)*s))
                    *s = toupper((int)(unsigned char)*s);
                s++;
            }
        } else
#endif /* KANJI_WIN95_COMPATIBILITY */
#endif /* UNUSED_CODE */
        {
            if (islower((int)(unsigned char)*s))
                *s = toupper((int)(unsigned char)*s);
            s++;
        }
    }
}