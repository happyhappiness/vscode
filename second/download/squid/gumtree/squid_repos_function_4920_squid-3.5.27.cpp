void
ACLFilledChecklist::markSourceDomainChecked()
{
    assert (!finished() && !sourceDomainChecked());
    sourceDomainChecked_ = true;
}