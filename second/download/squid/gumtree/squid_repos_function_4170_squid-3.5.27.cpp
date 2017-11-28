bool Adaptation::Icap::ModXact::shouldAllow206any()
{
    return TheConfig.allow206_enable && service().allows206() &&
           virginBody.expected(); // no need for 206 without a body
}