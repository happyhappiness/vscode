void
HttpMsg::setContentLength(int64_t clen)
{
    header.delById(Http::HdrType::CONTENT_LENGTH); // if any
    header.putInt64(Http::HdrType::CONTENT_LENGTH, clen);
    content_length = clen;
}