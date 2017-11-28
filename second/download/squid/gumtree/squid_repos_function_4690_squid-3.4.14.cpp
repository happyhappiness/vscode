int
ACLRandom::match(ACLChecklist *cl)
{
    // make up the random value
    double random = ((double)rand() / (double)RAND_MAX);

    debugs(28, 3, "ACL Random: " << name << " " << pattern << " test: " << data << " > " << random << " = " << ((data > random)?"MATCH":"NO MATCH") );
    return (data > random)?1:0;
}