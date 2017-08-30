  for(std::vector<cmStdString>::iterator i = originalLinkItems.begin();

      i != originalLinkItems.end(); ++i)

    {

    // Parse out the prefix, base, and suffix components of the

    // library name.  If the name matches that of a shared or static

    // library then set the link type accordingly.

    //

    // Search for shared library names first because some platforms

    // have shared libraries with names that match the static library

    // pattern.  For example cygwin and msys use the convention

    // libfoo.dll.a for import libraries and libfoo.a for static

    // libraries.  On AIX a library with the name libfoo.a can be

    // shared!

    if(this->ExtractSharedLibraryName.find(*i))

      {

#ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG

      fprintf(stderr, "shared regex matched [%s] [%s] [%s]\n",

