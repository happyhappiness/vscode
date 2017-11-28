void
CheckHasExplicitWorks()
{
    assert (HasExplicit::Instances() == 0);
    HasExplicit *one = new HasExplicit;
    assert (HasExplicit::Instances() == 1);
    HasExplicit *two = new HasExplicit;
    assert (HasExplicit::Instances() == 2);
    *two = *one;
    assert (HasExplicit::Instances() == 2);
    assert (HasExplicit::Assignments() == 1);
    *two = *one;
    assert (HasExplicit::Instances() == 2);
    assert (HasExplicit::Assignments() == 2);
    HasExplicit *three = new HasExplicit(*two);
    assert (HasExplicit::Instances() == 3);
    delete three;
    assert (HasExplicit::Instances() == 2);
    delete one;
    assert (HasExplicit::Instances() == 1);
    delete two;
    assert (HasExplicit::Instances() == 0);
    HasExplicit::Assignments(0);
    assert (HasExplicit::Assignments() == 0);
}