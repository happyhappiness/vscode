  return this->CacheManager->GetCacheValue(name);
}

void cmake::AddDefaultCommands()
{
  std::list<cmCommand*> commands;
