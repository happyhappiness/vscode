{
  State& lstate = reinterpret_cast<State&>(state);

  // Collect all the bytes for this codepoint.
  char buf[4];
  memcpy(buf, lstate.partial, lstate.buffered);
  buf[lstate.buffered] = *from_next;

  // Convert the encoding.
  wchar_t wbuf[2];
  int wlen =
    MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, buf, size, wbuf, 2);
  if (wlen <= 0) {
    return std::codecvt_base::error;
  }

  int tlen = WideCharToMultiByte(m_codepage, 0, wbuf, wlen, to_next,
                                 to_end - to_next, NULL, NULL);
  if (tlen <= 0) {
    if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
      return std::codecvt_base::partial;
    }
    return std::codecvt_base::error;
  }

  // Move past the now-consumed byte in the input buffer.
  ++from_next;

  // Move past the converted codepoint in the output buffer.
  to_next += tlen;

  // Re-initialize the state for the next codepoint to start.
  lstate = State();

  return std::codecvt_base::ok;
}