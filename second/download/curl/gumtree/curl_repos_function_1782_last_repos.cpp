unsigned short curlx_sltous(long slnum)
{
#ifdef __INTEL_COMPILER
#  pragma warning(push)
#  pragma warning(disable:810) /* conversion may lose significant bits */
#endif

  DEBUGASSERT(slnum >= 0);
  DEBUGASSERT((unsigned long) slnum <= (unsigned long) CURL_MASK_USHORT);
  return (unsigned short)(slnum & (long) CURL_MASK_USHORT);

#ifdef __INTEL_COMPILER
#  pragma warning(pop)
#endif
}