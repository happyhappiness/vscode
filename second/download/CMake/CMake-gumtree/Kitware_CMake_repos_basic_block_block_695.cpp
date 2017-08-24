{
    std::advance(pivot, *remIt - prevRem);
    prevRem = *remIt;
    writer = ContainerAlgorithms::RemoveN(writer, pivot, count);
  }