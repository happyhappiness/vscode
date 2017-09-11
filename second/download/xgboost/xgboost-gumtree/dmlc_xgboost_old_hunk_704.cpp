                    }
                }
                if (mparam.num_pbuffer != 0){
                    pred_buffer.resize(mparam.num_pbuffer);
                    pred_counter.resize(mparam.num_pbuffer);
                    utils::Assert(fi.Read(&pred_buffer[0], pred_buffer.size()*sizeof(float)) != 0);
                    utils::Assert(fi.Read(&pred_counter[0], pred_counter.size()*sizeof(unsigned)) != 0);
                }
