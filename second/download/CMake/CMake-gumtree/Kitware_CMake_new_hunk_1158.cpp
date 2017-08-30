}
inline const char* Getcwd(char* buf, unsigned int len)
{
  return getcwd(buf, len);
}

inline int Chdir(const char* dir)
