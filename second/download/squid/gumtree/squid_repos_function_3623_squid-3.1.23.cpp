void
IpIntercept::StopInterception(const char *str)
{
    if (intercept_active) {
        debugs(89, DBG_IMPORTANT, "Stopping IP interception: " << str);
        intercept_active = 0;
    }
}