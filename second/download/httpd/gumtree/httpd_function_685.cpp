static void mod_info_html_cmd_string(request_rec *r, const char *string,
                                     int close)
{
    const char *s;

    s = string;
    /* keep space for \0 byte */
    while (*s) {
        if (*s == '<') {
	    if (close) {
                ap_rputs("&lt;/", r);
	    } else {
                ap_rputs("&lt;", r);
	    }
        }
        else if (*s == '>') {
            ap_rputs("&gt;", r);
        }
        else if (*s == '&') {
            ap_rputs("&amp;", r);
        }
	else if (*s == ' ') {
	    if (close) {
	        ap_rputs("&gt;", r);
	        break;
	    } else {
                ap_rputc(*s, r);
            }
	} else {
            ap_rputc(*s, r);
        }
        s++;
    }
}