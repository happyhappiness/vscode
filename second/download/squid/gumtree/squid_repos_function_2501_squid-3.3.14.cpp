void
FtpStateData::listingFinish()
{
    // TODO: figure out what this means and how to show it ...

    if (flags.listformat_unknown && !flags.tried_nlst) {
        printfReplyBody("<a href=\"%s/;type=d\">[As plain directory]</a>\n",
                        flags.dir_slash ? rfc1738_escape_part(old_filepath) : ".");
    } else if (typecode == 'D') {
        const char *path = flags.dir_slash ? filepath : ".";
        printfReplyBody("<a href=\"%s/\">[As extended directory]</a>\n", rfc1738_escape_part(path));
    }
}