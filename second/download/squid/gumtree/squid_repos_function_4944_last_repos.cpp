bool
Rock::SwapDir::allowOptionReconfigure(const char *const option) const
{
    return strcmp(option, "slot-size") != 0 &&
           ::SwapDir::allowOptionReconfigure(option);
}