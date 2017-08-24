{
  typename InputRange::const_iterator remIt = rem.begin();
  typename InputRange::const_iterator remEnd = rem.end();
  const typename Range::iterator rangeEnd = r.end();
  if (remIt == remEnd) {
    return rangeEnd;
  }

  typename Range::iterator writer = r.begin();
  std::advance(writer, *remIt);
  typename Range::iterator pivot = writer;
  typename InputRange::value_type prevRem = *remIt;
  ++remIt;
  size_t count = 1;
  for (; writer != rangeEnd && remIt != remEnd; ++count, ++remIt) {
    std::advance(pivot, *remIt - prevRem);
    prevRem = *remIt;
    writer = ContainerAlgorithms::RemoveN(writer, pivot, count);
  }
  return ContainerAlgorithms::RemoveN(writer, rangeEnd, count);
}