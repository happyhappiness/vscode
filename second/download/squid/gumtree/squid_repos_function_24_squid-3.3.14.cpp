static void
error_html(const char *msg)
{
    printf("Content-Type: text/html\r\n\r\n");
    printf("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
    printf("<HTML><HEAD><TITLE>Cache Manager Error</TITLE>\n");
    printf("<STYLE type=\"text/css\"><!--BODY{background-color:#ffffff;font-family:verdana,sans-serif}--></STYLE></HEAD>\n");
    printf("<BODY><H1>Cache Manager Error</H1>\n");
    printf("<P>\n%s</P>\n", html_quote(msg));
    print_trailer();
}