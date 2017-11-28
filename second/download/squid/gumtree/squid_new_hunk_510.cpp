    FinalizeEach(AllServices(), "message adaptation services");
    FinalizeEach(AllGroups(), "message adaptation service groups");
    FinalizeEach(AllRules(), "message adaptation access rules");
}

void
Adaptation::Config::ParseServiceSet()
{
    Adaptation::Config::ParseServiceGroup(new ServiceSet);
}

void
