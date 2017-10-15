  element->set_column(1);
  element->set_interval(1);

  element->push_back("Peer info:");

  element->push_back("");
  element->push_column("Address:",   te_command("cat=$p.address=,:,$p.port="));
  element->push_column("Id:",        te_command("p.id_html="));
  element->push_column("Client:",    te_command("p.client_version="));
  element->push_column("Options:",   te_command("p.options_str="));
  element->push_column("Connected:", te_command("if=$p.is_incoming=,incoming,outgoing"));
  element->push_column("Encrypted:", te_command("if=$p.is_encrypted=,yes,$p.is_obfuscated=,handshake,no"));

  element->push_back("");
  element->push_column("Snubbed:",   te_command("if=$p.is_snubbed=,yes,no"));
  element->push_column("Done:",      te_command("p.completed_percent="));
  element->push_column("Rate:",      te_command("cat=$convert.kb=$p.up_rate=,\\ KB\\ ,$convert.kb=$p.down_rate=,\\ KB"));
  element->push_column("Total:",     te_command("cat=$convert.kb=$p.up_total=,\\ KB\\ ,$convert.kb=$p.down_total=,\\ KB"));

  element->set_column_width(element->column_width() + 1);
  element->set_error_handler(new display::TextElementCString("No peer selected."));

  return element;
}
