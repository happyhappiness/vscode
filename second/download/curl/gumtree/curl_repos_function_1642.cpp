unsigned int curlx_sltoui(long slnum)
{
#ifdef __INTEL_COMPILER
#  pragma warning(push)
#  pragma warning(disable:810) /* conversion may lose significant bits */
#endif

  DEBUGASSERT(slnum >= 0);
#if (SIZEOF_INT < CURL_SIZEOF_LONG)
  DEBUGASSERT((unsigned long) slnum <= (unsigned long) CURL_MASK_UINT);
#endif
  return (unsigned int)(slnum & (long) CURL_MASK_UINT);

#ifdef __INTEL_COMPILER
#  pragma warning(pop)
#endif
}