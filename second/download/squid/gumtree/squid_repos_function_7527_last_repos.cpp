size_t Ssl::CertificateDb::getFileSize(std::string const & filename) {
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file)
        return 0;
    file.seekg(0, std::ios_base::end);
    const std::streampos file_size = file.tellg();
    if (file_size < 0)
        return 0;
    return ((static_cast<size_t>(file_size) + fs_block_size - 1) / fs_block_size) * fs_block_size;
}