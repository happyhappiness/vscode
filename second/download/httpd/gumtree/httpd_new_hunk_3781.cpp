/* ------------------------------------------------------- */

/* display copyright information */
static void copyright(void)
{
    if (!use_html) {
        printf("This is ApacheBench, Version %s\n", AP_AB_BASEREVISION " <$Revision: 1663405 $>");
        printf("Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/\n");
        printf("Licensed to The Apache Software Foundation, http://www.apache.org/\n");
        printf("\n");
    }
    else {
        printf("<p>\n");
        printf(" This is ApacheBench, Version %s <i>&lt;%s&gt;</i><br>\n", AP_AB_BASEREVISION, "$Revision: 1663405 $");
        printf(" Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/<br>\n");
        printf(" Licensed to The Apache Software Foundation, http://www.apache.org/<br>\n");
        printf("</p>\n<p>\n");
    }
}

