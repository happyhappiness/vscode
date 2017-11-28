void
HttpStateData::proceedAfter1xx()
{
    Must(flags.handling1xx);

    debugs(11, 2, HERE << "consuming " << header_bytes_read <<
           " header and " << reply_bytes_read << " body bytes read after 1xx");
    header_bytes_read = 0;
    reply_bytes_read = 0;

    CallJobHere(11, 3, this, HttpStateData, HttpStateData::processReply);
}