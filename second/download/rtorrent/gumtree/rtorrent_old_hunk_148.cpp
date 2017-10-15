void
apply_load(Control* m, const std::string& arg) {
  m->core()->try_create_download_expand(arg, false, false, true);
}

void
apply_load_start(Control* m, const std::string& arg) {
  m->core()->try_create_download_expand(arg, true, false, true);
}

void
apply_stop_untied(Control* m) {
  core::Manager::DListItr itr = m->core()->download_list()->begin();

  while ((itr = std::find_if(itr, m->core()->download_list()->end(),
			     rak::on(rak::bind2nd(std::mem_fun(&core::Download::variable_string), "tied_to_file"),
				     std::not1(std::mem_fun_ref(&std::string::empty)))))
	 != m->core()->download_list()->end()) {
    rak::file_stat fs;

    if (!fs.update(rak::path_expand((*itr)->variable_string("tied_to_file")))) {
      (*itr)->variable()->set("tied_to_file", std::string());
      m->core()->download_list()->stop(*itr);
    }

    ++itr;
  }
}

void
apply_close_untied(Control* m) {
  core::Manager::DListItr itr = m->core()->download_list()->begin();

  while ((itr = std::find_if(itr, m->core()->download_list()->end(),
			     rak::on(rak::bind2nd(std::mem_fun(&core::Download::variable_string), "tied_to_file"),
				     std::not1(std::mem_fun_ref(&std::string::empty)))))
	 != m->core()->download_list()->end()) {
    rak::file_stat fs;

    if (!fs.update(rak::path_expand((*itr)->variable_string("tied_to_file")))) {
      (*itr)->variable()->set("tied_to_file", std::string());
      m->core()->download_list()->close(*itr);
    }

    ++itr;
  }
}

void
apply_remove_untied(Control* m) {
  core::Manager::DListItr itr = m->core()->download_list()->begin();

  while ((itr = std::find_if(itr, m->core()->download_list()->end(),
			     rak::on(rak::bind2nd(std::mem_fun(&core::Download::variable_string), "tied_to_file"),
				     std::not1(std::mem_fun_ref(&std::string::empty)))))
	 != m->core()->download_list()->end()) {
    rak::file_stat fs;

    if (!fs.update(rak::path_expand((*itr)->variable_string("tied_to_file")))) {
      (*itr)->variable()->set("tied_to_file", std::string());
      m->core()->download_list()->stop(*itr);
      itr = m->core()->download_list()->erase(itr);

    } else {
      ++itr;
    }
  }
}

void
apply_encoding_list(__UNUSED Control* m, const std::string& arg) {
  torrent::encoding_list()->push_back(arg);
