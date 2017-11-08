static inline int git_CC_EVP_EncodeBlock(unsigned char *out,
		const unsigned char *in, int inlen)
{
	CFErrorRef err;
	SecTransformRef encoder;
	CFDataRef input, output;
	CFIndex length;

	encoder = SecEncodeTransformCreate(kSecBase64Encoding, &err);
	git_CC_error_check("SecEncodeTransformCreate failed: %ld", err);

	input = CFDataCreate(kCFAllocatorDefault, in, inlen);
	SecTransformSetAttribute(encoder, kSecTransformInputAttributeName,
			input, &err);
	git_CC_error_check("SecTransformSetAttribute failed: %ld", err);

	output = SecTransformExecute(encoder, &err);
	git_CC_error_check("SecTransformExecute failed: %ld", err);

	length = CFDataGetLength(output);
	CFDataGetBytes(output, CFRangeMake(0, length), out);

	CFRelease(output);
	CFRelease(input);
	CFRelease(encoder);

	return (int)strlen((const char *)out);
}