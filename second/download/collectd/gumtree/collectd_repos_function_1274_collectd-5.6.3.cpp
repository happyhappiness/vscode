static grpc::string read_file(const char *filename)
{
	std::ifstream f;
	grpc::string s, content;

	f.open(filename);
	if (!f.is_open()) {
		ERROR("grpc: Failed to open '%s'", filename);
		return "";
	}

	while (std::getline(f, s)) {
		content += s;
		content.push_back('\n');
	}
	f.close();
	return content;
}