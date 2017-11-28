void
ACLChecklist::markFinished()
{
    assert (!finished() && !asyncInProgress());
    finished_ = true;
    debugs(28, 3, "ACLChecklist::markFinished: " << this <<
           " checklist processing finished");
}