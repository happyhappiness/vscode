		      itr == *m_focus ? '*' : ' ',
		      (double)itr->get_download().get_bytes_total() / (double)(1 << 20),
		      (double)itr->get_download().get_rate_up() / 1024.0,
		      (double)itr->get_download().get_rate_down() / 1024.0,
		      (double)itr->get_download().get_bytes_up() / (double)(1 << 20));
    
    m_canvas->print(0, pos++, "%c %s", itr == *m_focus ? '*' : ' ', print_download_status(&*itr).c_str());

    ++itr;
  }    
}

}
