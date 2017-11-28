bool HttpReply::parseFirstLine(const char *blk_start, const char *blk_end)
{
    return httpStatusLineParse(&sline, protoPrefix, blk_start, blk_end);
}