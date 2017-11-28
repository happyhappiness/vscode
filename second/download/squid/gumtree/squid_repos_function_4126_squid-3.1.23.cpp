void Ssl::CertificateDb::Row::setValue(size_t cell, char const * value)
{
    assert(cell < width);
    if (row[cell]) {
        free(row[cell]);
    }
    if (value) {
        row[cell] = static_cast<char *>(xmalloc(sizeof(char) * (strlen(value) + 1)));
        memcpy(row[cell], value, sizeof(char) * (strlen(value) + 1));
    } else
        row[cell] = NULL;
}