static int inline git_CC_EVP_DecodeBlock(unsigned char *out,
		const unsigned char *in, int inlen)
{
	CFErrorRef err;
	SecTransformRef decoder;
	CFDataRef input, output;
	CFIndex length;

	decoder = SecDecodeTransformCreate(kSecBase64Encoding, &err);
	git_CC_error_check("SecEncodeTransformCreate failed: %ld", err);

	input = CFDataCreate(kCFAllocatorDefault, in, inlen);
	SecTransformSetAttribute(decoder, kSecTransformInputAttributeName,
			input, &err);
	git_CC_error_check("SecTransformSetAttribute failed: %ld", err);

	output = SecTransformExecute(decoder, &err);
	git_CC_error_check("SecTransformExecute failed: %ld", err);

	length = CFDataGetLength(output);
	CFDataGetBytes(output, CFRangeMake(0, length), out);

	CFRelease(output);
	CFRelease(input);
	CFRelease(decoder);

	return (int)strlen((const char *)out);
}