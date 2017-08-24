{
  if (!c.Length) {
    return os;
  }
  os.write(c.Data, c.Length);
  os.flush();
  return os;
}