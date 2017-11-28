void
HttpHdrRangeIter::updateSpec()
{
    assert (debt_size == 0);
    assert (valid);

    if (pos.incrementable()) {
        debt(currentSpec()->length);
    }
}