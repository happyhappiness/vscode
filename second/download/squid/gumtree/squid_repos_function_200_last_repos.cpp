int
main(int argc, char **argv)
{
    assert (BaseVirtual::Calls.news() == 0);
    assert (BaseVirtual::Calls.deletes() == 0);
    assert (ChildVirtual::Calls.news() == 0);
    assert (ChildVirtual::Calls.deletes() == 0);
    BaseVirtual *aBase = new ChildVirtual;
    assert (BaseVirtual::Calls.news() == 0);
    assert (BaseVirtual::Calls.deletes() == 0);
    assert (ChildVirtual::Calls.news() == 1);
    assert (ChildVirtual::Calls.deletes() == 0);
    BaseVirtual::DeleteABase(aBase);
    assert (BaseVirtual::Calls.news() == 0);
    assert (BaseVirtual::Calls.deletes() == 0);
    assert (ChildVirtual::Calls.news() == 1);
    assert (ChildVirtual::Calls.deletes() == 1);
    // deleting NULL works.
    BaseVirtual::DeleteABase(NULL);
    assert (BaseVirtual::Calls.news() == 0);
    assert (BaseVirtual::Calls.deletes() == 0);
    assert (ChildVirtual::Calls.news() == 1);
    assert (ChildVirtual::Calls.deletes() == 1);
    return 0;
}