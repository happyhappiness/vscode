return curl_maprintf("%u%.2s-%.2s-%.2s %.2s:%.2s:%.2s %.*s",
                       20 - (*beg >= '5'), beg, beg + 2, beg + 4,
                       beg + 6, beg + 8, sec,
                       tzl, tzp);