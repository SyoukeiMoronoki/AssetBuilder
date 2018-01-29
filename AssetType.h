#pragma once

#include <regex>
#include <string>
#include <set>

#include "JsonParser.h"

// =================================================================
// AssetType
// =================================================================
class AssetType
{
public:
  AssetType(const JsonNode* node);
  virtual ~AssetType() {}

public:
  void GetIncludePaths(std::set<std::string>* dest) const;

  void CreateHead(std::string* header, std::string* cpp) const;
  void CreateFoot(std::string* header, std::string* cpp) const;
  virtual void CreateProgram(std::string* header, std::string* cpp, const std::map<std::string, std::string>& paths) const = 0;

public:
  virtual const std::string ToString(T_UINT8 depth = 0) const;

public:
  inline const std::string& GetName() const
  {
    return this->name_;
  }
  inline const std::string& GetTypeName() const
  {
    return this->type_name_;
  }

private:
  std::string name_;
  std::string type_name_;
  std::set<std::string> includes_;
};

// =================================================================
// AssetType_SubAsset
// =================================================================
class AssetType_SubAsset : public AssetType
{
public:
  AssetType_SubAsset(AssetType* base, const JsonNode* node);
  ~AssetType_SubAsset();

public:
  void CreateProgram(std::string* header, std::string* cpp, const std::map<std::string, std::string>& paths) const override;

public:
  const std::string ToString(T_UINT8 depth = 0) const override;

protected:
  std::set<AssetType_SubAsset*> sub_assets_;

private:
  AssetType* base_asset_;

};

// =================================================================
// AssetType_File
// =================================================================
class AssetType_File : public AssetType_SubAsset
{
public:
  enum AssetOption
  {
    kAssetOption_Folder,
  };

public:
  AssetType_File(const JsonNode* node);

public:
  bool IgnoreCheck(const std::string& path) const;
  bool OptionCheck(AssetOption option) const;

  void CreateProgram(std::string* header, std::string* cpp, const std::map<std::string, std::string>& paths) const override;

public:
  const std::string ToString(T_UINT8 depth = 0) const override;

private:
  std::set<std::string> ignores_;
  std::regex ignore_regex_;
  std::set<std::string> options_;
};