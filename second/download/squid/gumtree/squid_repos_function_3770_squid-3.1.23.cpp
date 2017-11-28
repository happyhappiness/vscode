void
Adaptation::Config::Finalize(bool enabled)
{
    Enabled = enabled;
    debugs(93,1, "Adaptation support is " << (Enabled ? "on" : "off."));

    FinalizeEach(AllServices(), "message adaptation services");
    FinalizeEach(AllGroups(), "message adaptation service groups");
    FinalizeEach(AllRules(), "message adaptation access rules");
}