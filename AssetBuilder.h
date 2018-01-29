#pragma once

#include <string>
#include <vector>

#include "AssetData.h"

class AssetBuilder
{
public:
  AssetBuilder(const char* path);
  ~AssetBuilder();

public:
  bool Load();
  void CreateProgram(std::string* header, std::string* cpp);

public:
  const std::string ToString();

private:
  std::string config_path_;
  std::string engine_name_;
  std::string asset_name_;
  std::string target_path_;
  std::string source_path_;
  std::vector<AssetData*> asset_datas_;

};