void
ACLChecklist::completeNonBlocking()
{
    assert(!asyncInProgress());

    if (!finished())
        calcImplicitAnswer();

    cbdataReferenceDone(accessList);
    checkCallback(currentAnswer());
}