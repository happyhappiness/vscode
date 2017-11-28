void
Ip::Intercept::StopTransparency(const char *str)
{
    if (transparentActive_) {
        debugs(89, DBG_IMPORTANT, "Stopping full transparency: " << str);
        transparentActive_ = 0;
    }
}