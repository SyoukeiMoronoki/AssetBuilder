#include "AssetType.h"
#include <iostream>

// =================================================================
// AssetType
// =================================================================
AssetType::AssetType(const JsonNode* node)
  : includes_()
{
  this->name_ = node->GetString("Name")->StringValue();
  this->type_name_ = node->GetString("TypeName")->StringValue();

  const JsonList* includes = node->GetList("Includes");
  if (includes)
  {
    int includes_count = includes->GetSize();
    for (int i = 0; i < includes_count; ++i)
    {
      this->includes_.insert(*includes->GetString(i));
    }
  }

}

void AssetType::GetIncludePaths(std::set<std::string>* dest) const
{
  for (std::string include : this->includes_)
  {
    dest->insert(include);
  }
}

void AssetType::CreateHead(std::string* header, std::string* cpp) const
{
  //Header head
  header->append("namespace " + this->name_ + "\n");
  header->append("{\n");

  //cpp head
  cpp->append("namespace " + this->name_ + "\n");
  cpp->append("{\n");
}

void AssetType::CreateFoot(std::string* header, std::string* cpp) const
{
  //Header bottom
  header->append("} // namespace " + this->name_ + "\n");

  //cpp bottom
  cpp->append("} // namespace " + this->name_ + "\n");
}

const std::string AssetType::ToString(T_UINT8 depth) const
{
  std::string ret = std::string();

  for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
  ret.append("Name = ");
  ret.append(this->name_);
  ret.append("\n");

  for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
  ret.append("TypeName = ");
  ret.append(this->type_name_);
  ret.append("\n");

  if (this->includes_.size() > 0)
  {
    for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
    ret.append("Includes = ");
    for (std::string include : this->includes_)
    {
      ret.append(include);
      ret.append(", ");
    }
    ret.append("\n");
  }

  return ret;
}

// =================================================================
// AssetType_SubAsset
// =================================================================
AssetType_SubAsset::AssetType_SubAsset(AssetType* base, const JsonNode* node)
  : AssetType(node)
  , base_asset_(base)
{
  const JsonList* sub_assets = node->GetList("SubAssetTypes");
  if (sub_assets)
  {
    int sub_assets_count = sub_assets->GetSize();
    for (int i = 0; i < sub_assets_count; ++i)
    {
      this->sub_assets_.insert(new AssetType_SubAsset(this, sub_assets->GetNode(i)));
    }
  }
}

AssetType_SubAsset::~AssetType_SubAsset()
{
  for (AssetType* sub_asset : this->sub_assets_)
  {
    delete sub_asset;
  }
}

void AssetType_SubAsset::CreateProgram(std::string* header, std::string* cpp, const std::map<std::string, std::string>& paths) const
{
  this->CreateHead(header, cpp);

  //Body
  std::string type_name = std::string();
  if (this->GetName() == this->GetTypeName())
  {
    type_name.append("class ");
  }
  type_name.append(this->GetTypeName());
  for (const auto& pair : paths)
  {
    header->append("extern " + type_name + " " + pair.first + ";\n");
    cpp->append(type_name + " " + pair.first + "(" + this->base_asset_->GetName() + "::" + pair.first + ");\n");
  }

  this->CreateFoot(header, cpp);

  header->append("\n");
  cpp->append("\n");
}

const std::string AssetType_SubAsset::ToString(T_UINT8 depth) const
{
  std::string ret = AssetType::ToString(depth);
  if (this->sub_assets_.size() > 0)
  {
    for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
    ret.append("SubAssetTypes = [\n");
    for (AssetType_SubAsset* sub_asset : this->sub_assets_)
    {
      for (T_UINT8 i = 0; i < depth + 1; ++i) ret.append("\t");
      ret.append("{\n");
      ret.append(sub_asset->ToString(depth + 2));
      for (T_UINT8 i = 0; i < depth + 1; ++i) ret.append("\t");
      ret.append("},\n");
    }
    for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
    ret.append("]\n");
  }
  return ret;
}


// =================================================================
// AssetType_File
// =================================================================
AssetType_File::AssetType_File(const JsonNode* node)
  : AssetType_SubAsset(nullptr, node)
  , ignores_()
{
  std::string regex = std::string();
  const JsonList* ignores = node->GetList("Ignores");
  if (ignores)
  {
    int ignore_count = ignores->GetSize();
    for (int i = 0; i < ignore_count; ++i)
    {
      if (i != 0)
      {
        regex.append("|");
      }
      this->ignores_.insert(*ignores->GetString(i));
      regex.append("(");
      regex.append(*ignores->GetString(i));
      regex.append(")");
    }
  }
  try
  {
    this->ignore_regex_ = std::regex(regex);
  }
  catch (std::regex_error& e)
  {
    std::cout << e.what() << std::endl;
    std::cout << this->ToString(1) << "Ë " << regex << std::endl;
    getchar();
  }

  const JsonList* options = node->GetList("Options");
  if (options)
  {
    int options_count = options->GetSize();
    for (int i = 0; i < options_count; ++i)
    {
      this->options_.insert(*options->GetString(i));
    }
  }
}

bool AssetType_File::IgnoreCheck(const std::string& path) const
{
  return std::regex_match(path, this->ignore_regex_);
}

std::string OptionToString(AssetType_File::AssetOption op)
{
  if (op == AssetType_File::kAssetOption_Folder)
  {
    return "Folder";
  }
  if (op == AssetType_File::kAssetOption_Folder)
  {
    return "Folder";
  }
  return "";
}

bool AssetType_File::OptionCheck(AssetOption option) const
{
  std::string op = OptionToString(option);
  for (const std::string& str : this->options_)
  {
    if (op == str)
    {
      return true;
    }
  }
  return false;
}

void AssetType_File::CreateProgram(std::string* header, std::string* cpp, const std::map<std::string, std::string>& paths) const
{
  this->CreateHead(header, cpp);

  //Body
  std::string type_name = std::string();
  if (this->GetName() == this->GetTypeName())
  {
    type_name.append("class ");
  }
  type_name.append(this->GetTypeName());
  for (const auto& pair : paths)
  {
    header->append("extern " + type_name + " " + pair.first + ";\n");
    cpp->append(type_name + " " + pair.first + "(\"" + pair.second + "\");\n");
  }

  this->CreateFoot(header, cpp);

  header->append("\n");
  cpp->append("\n");

  for (AssetType_SubAsset* sub_asset : this->sub_assets_)
  {
    sub_asset->CreateProgram(header, cpp, paths);
  }
}

const std::string AssetType_File::ToString(T_UINT8 depth) const
{
  std::string ret = AssetType_SubAsset::ToString(depth);

  if (this->ignores_.size() > 0)
  {
    for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
    ret.append("Ignores = ");
    for (std::string ignore : this->ignores_)
    {
      ret.append(ignore);
      ret.append(", ");
    }
    ret.append("\n");
  }

  if (this->options_.size() > 0)
  {
    for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
    ret.append("Options = ");
    for (std::string option : this->options_)
    {
      ret.append(option);
      ret.append(", ");
    }
    ret.append("\n");
  }

  return ret;
}
