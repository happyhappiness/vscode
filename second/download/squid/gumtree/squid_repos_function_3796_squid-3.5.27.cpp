void
Ip::Intercept::StopInterception(const char *str)
{
    if (interceptActive_) {
        debugs(89, DBG_IMPORTANT, "Stopping IP interception: " << str);
        interceptActive_ = 0;
    }
}