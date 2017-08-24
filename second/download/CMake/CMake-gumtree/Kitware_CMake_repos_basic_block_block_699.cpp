{
    const typename std::vector<T>::iterator low = std::lower_bound(
      unique.begin(), unique.end(), API::uniqueValue(it), API::lessThan);
    if (low == unique.end() || API::valueCompare(low, it)) {
      unique.insert(low, API::uniqueValue(it));
    } else {
      indices.push_back(count);
    }
  }