bool
HttpReply::parseFirstLine(const char *blk_start, const char *blk_end)
{
    return sline.parse(protoPrefix, blk_start, blk_end);
}