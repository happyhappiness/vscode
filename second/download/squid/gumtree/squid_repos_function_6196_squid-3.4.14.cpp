void
esiSequence::wontFail()
{
    assert (!failed);
    mayFail_ = false;
}