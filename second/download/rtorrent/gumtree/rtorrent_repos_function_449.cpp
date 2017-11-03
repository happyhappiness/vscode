Log::iterator
Log::find_older(rak::timer t) {
  return std::find_if(begin(), end(), rak::on(rak::mem_ref(&Type::first), std::bind2nd(std::less_equal<rak::timer>(), t)));
}