void
CossMemBuf::write(CossSwapDir * SD)
{
    ++ StoreFScoss::GetInstance().stats.stripe_write.ops;
    debugs(79, 3, "CossMemBuf::write: offset " << diskstart << ", len " << (diskend - diskstart));
    flags.writing = 1;
    /* XXX Remember that diskstart/diskend are block offsets! */
    SD->theFile->write(new CossWrite(WriteRequest((char const *)&buffer, diskstart, diskend - diskstart, NULL), this));
}