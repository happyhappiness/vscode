return curl_maprintf("%.4s-%.2s-%.2s %.2s:%.2s:%c%c%s%.*s%s%.*s",
                       beg, beg + 4, beg + 6,
                       beg + 8, beg + 10, sec1, sec2,
                       fracl? ".": "", fracl, fracp,
                       sep, tzl, tzp);