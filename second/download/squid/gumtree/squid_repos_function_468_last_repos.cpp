void
HttpReply::redirect(Http::StatusCode status, const char *loc)
{
    HttpHeader *hdr;
    sline.set(Http::ProtocolVersion(), status, NULL);
    hdr = &header;
    hdr->putStr(Http::HdrType::SERVER, APP_FULLNAME);
    hdr->putTime(Http::HdrType::DATE, squid_curtime);
    hdr->putInt64(Http::HdrType::CONTENT_LENGTH, 0);
    hdr->putStr(Http::HdrType::LOCATION, loc);
    date = squid_curtime;
    content_length = 0;
}