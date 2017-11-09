void GUSISetupConfig()
{
	GUSIConfiguration * config =
		GUSIConfiguration::CreateInstance(GUSIConfiguration::kNoResource);

	config->ConfigureDefaultTypeCreator('TEXT', 'CWIE');
	config->ConfigureSuffices(
		sizeof(sSuffices)/sizeof(GUSIConfiguration::FileSuffix)-1, sSuffices);
}