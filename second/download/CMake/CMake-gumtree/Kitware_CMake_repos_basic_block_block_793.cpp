{
  to_next = to;
  if (m_noconv) {
    return std::codecvt_base::noconv;
  }
#if defined(_WIN32)
  State& lstate = reinterpret_cast<State&>(state);
  if (lstate.buffered != 0) {
    return this->DecodePartial(state, to_next, to_end);
  }
  return std::codecvt_base::ok;
#else
  static_cast<void>(state);
  static_cast<void>(to_end);
  return std::codecvt_base::ok;
#endif
}