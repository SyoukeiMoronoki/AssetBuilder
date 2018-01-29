#pragma once

#include "AssetType.h"

class AssetData
{
public:
  AssetData(const JsonNode* node);

public:
  void Load(const std::string& asset_name, const std::string& directory_path);
  void CreateProgram(std::string* header, std::string* cpp);

public:
  const std::string ToString(T_UINT8 depth = 0) const;
  
public:
  inline const AssetType_File& GetAssetType() const
  {
    return this->type_;
  }


private:
  AssetType_File type_;
  //ID, Path
  std::map<std::string, std::string> asset_paths_;

};