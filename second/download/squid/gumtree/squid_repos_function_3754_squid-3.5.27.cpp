void
HttpHdrRangeIter::updateSpec()
{
    assert (debt_size == 0);
    assert (valid);

    if (pos != end) {
        debt(currentSpec()->length);
    }
}