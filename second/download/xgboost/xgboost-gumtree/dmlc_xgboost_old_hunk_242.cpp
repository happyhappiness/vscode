    data->resize(nthread);
    bytes_read_ += chunk.size;
    utils::Assert(chunk.size != 0, "LibSVMParser.FileData");
    char *head = reinterpret_cast<char*>(chunk.dptr);        
    #pragma omp parallel num_threads(nthread_)
    {
      // threadid
