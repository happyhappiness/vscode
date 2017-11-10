int transport_restrict_protocols(void)
{
	return !!protocol_whitelist();
}