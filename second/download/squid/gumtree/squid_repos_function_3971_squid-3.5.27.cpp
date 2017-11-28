void
Adaptation::Config::Finalize(bool enabled)
{
    Enabled = enabled;
    debugs(93, DBG_IMPORTANT, "Adaptation support is " << (Enabled ? "on" : "off."));

    FinalizeEach(AllServices(), "message adaptation services");
    FinalizeEach(AllGroups(), "message adaptation service groups");
    FinalizeEach(AllRules(), "message adaptation access rules");
}