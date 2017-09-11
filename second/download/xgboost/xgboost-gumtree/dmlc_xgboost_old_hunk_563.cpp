    ret.info.info.num_row = len;
    ret.info.info.num_col = src.info.num_col();

    utils::IIterator<RowBatch> *iter = src.fmat.RowIterator();
    iter->BeforeFirst();
    utils::Assert(iter->Next(), "slice");
    const RowBatch &batch = iter->Value();
