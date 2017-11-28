int
ACLRandom::match(ACLChecklist *)
{
    // make up the random value.
    // The fixed-value default seed is fine because we are
    // actually matching whether the random value is above
    // or below the configured threshold ratio.
    static std::mt19937 mt;
    static xuniform_real_distribution<> dist(0, 1);

    const double random = dist(mt);

    debugs(28, 3, "ACL Random: " << name << " " << pattern << " test: " << data << " > " << random << " = " << ((data > random)?"MATCH":"NO MATCH") );
    return (data > random)?1:0;
}