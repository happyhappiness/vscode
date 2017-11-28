void Ssl::CertificateDb::save()
{
    if (!db)
        throw std::runtime_error("The certificates database is not loaded");;

    // To save the db to file,  create a new BIO with BIO file methods.
    Ssl::BIO_Pointer out(BIO_new(BIO_s_file()));
    if (!out || !BIO_write_filename(out.get(), const_cast<char *>(db_full.c_str())))
        throw std::runtime_error("Failed to initialize " + db_full + " file for writing");;

    if (TXT_DB_write(out.get(), db.get()) < 0)
        throw std::runtime_error("Failed to write " + db_full + " file");
}