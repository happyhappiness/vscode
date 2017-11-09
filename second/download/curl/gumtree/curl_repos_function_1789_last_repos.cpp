size_t curlx_sitouz(int sinum)
{
#ifdef __INTEL_COMPILER
#  pragma warning(push)
#  pragma warning(disable:810) /* conversion may lose significant bits */
#endif

  DEBUGASSERT(sinum >= 0);
  return (size_t) sinum;

#ifdef __INTEL_COMPILER
#  pragma warning(pop)
#endif
}