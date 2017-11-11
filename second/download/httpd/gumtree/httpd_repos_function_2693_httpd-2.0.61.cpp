int NS(XmlParseXmlDecl)(int isGeneralTextEntity,
			const ENCODING *enc,
			const char *ptr,
			const char *end,
			const char **badPtr,
			const char **versionPtr,
			const char **versionEndPtr,
			const char **encodingName,
			const ENCODING **encoding,
			int *standalone)
{
  return doParseXmlDecl(NS(findEncoding),
			isGeneralTextEntity,
			enc,
			ptr,
			end,
			badPtr,
			versionPtr,
			versionEndPtr,
			encodingName,
			encoding,
			standalone);
}