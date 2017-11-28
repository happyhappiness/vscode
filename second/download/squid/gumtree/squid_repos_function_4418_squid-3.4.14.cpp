void Ssl::CertificateDb::deleteRow(const char **row, int rowIndex) {
    const std::string filename(cert_full + "/" + row[cnlSerial] + ".pem");
    sq_TXT_DB_delete_row(db.get(), rowIndex);

    subSize(filename);
    int ret = remove(filename.c_str());
    if (ret < 0 && errno != ENOENT)
        throw std::runtime_error("Failed to remove certficate file " + filename + " from db");
}