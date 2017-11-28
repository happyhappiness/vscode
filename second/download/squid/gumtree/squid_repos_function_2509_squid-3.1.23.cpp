void
FtpStateData::listingFinish()
{
    debugs(9,3,HERE);
    entry->buffer();
    printfReplyBody("</PRE>\n");

    if (flags.listformat_unknown && !flags.tried_nlst) {
        printfReplyBody("<A HREF=\"%s/;type=d\">[As plain directory]</A>\n",
                        flags.dir_slash ? rfc1738_escape_part(old_filepath) : ".");
    } else if (typecode == 'D') {
        const char *path = flags.dir_slash ? filepath : ".";
        printfReplyBody("<A HREF=\"%s/\">[As extended directory]</A>\n", rfc1738_escape_part(path));
    }

    printfReplyBody("<HR noshade size=\"1px\">\n");
    printfReplyBody("<ADDRESS>\n");
    printfReplyBody("Generated %s by %s (%s)\n",
                    mkrfc1123(squid_curtime),
                    getMyHostname(),
                    visible_appname_string);
    printfReplyBody("</ADDRESS></BODY></HTML>\n");
}