void
HttpMsg::setContentLength(int64_t clen)
{
    header.delById(HDR_CONTENT_LENGTH); // if any
    header.putInt64(HDR_CONTENT_LENGTH, clen);
    content_length = clen;
}