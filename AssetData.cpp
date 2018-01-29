#include "AssetData.h"
#include <Windows.h>
#include <algorithm>

#undef GetClassName

AssetData::AssetData(const JsonNode* node)
  : type_(node)
  , asset_paths_()
{
}

void Crawl(const AssetType_File& type, const std::string& target_directory_path, const std::string& target_asset_path, std::string directory_id, std::map<std::string, std::string>* dest)
{
  HANDLE handle;
  WIN32_FIND_DATA data;

  std::string find_file = target_directory_path + "*";
  handle = FindFirstFile(find_file.c_str(), &data);
  if (handle == INVALID_HANDLE_VALUE)
  {
    printf("error Asset File not found\n");
    getchar();
    return;
  }

  //directory_path�Ŏw�肳�ꂽ�f�B���N�g�����̂��ׂẴt�@�C��/�f�B���N�g���ɑ΂��������s��
  do
  {
    //�e�f�B���N�g���𖳎�
    if (
      (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
      (strcmp(data.cFileName, "..") == 0 || strcmp(data.cFileName, ".") == 0)
      )
    {
      continue;
    }
    if (type.IgnoreCheck(data.cFileName))
    {
      continue;
    }

    //�t�@�C�������L�����������������ꍇ�X�l�[�N�����ɕύX
    std::string snake_filename = data.cFileName;
    snake_filename = std::regex_replace(snake_filename, std::regex("([a-z])([A-Z])"), "$1_$2");

    //�t�@�C������啶���ɕϊ�
    std::string upper_filename = snake_filename;
    std::transform(upper_filename.begin(), upper_filename.end(), upper_filename.begin(), ::toupper);

    //�t�@�C��������g���q����菜��
    std::string::size_type pos;
    pos = upper_filename.find_last_of(".");
    upper_filename = upper_filename.substr(0, pos);
    
    //�v���O�����������̖��O(ID)�̍쐬
    std::string id = directory_id;

    //�f�B���N�g���������ꍇ�͂��̃f�B���N�g���ɑ΂��Ă��������s��
    if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
      if (id.length() > 0)
      {
        id.append("_");
      }
      id.append(upper_filename);
      Crawl(type, target_directory_path + data.cFileName + "/", target_asset_path + data.cFileName + "/", id, dest);
      continue;
    }

    if (!type.OptionCheck(AssetType_File::kAssetOption_Folder))
    {
      if (id.length() > 0)
      {
        id.append("_");
      }
      id.append(upper_filename);
    }
    (*dest)[id] = target_asset_path + data.cFileName;
  } while (FindNextFile(handle, &data));

  FindClose(handle);
}

void AssetData::Load(const std::string& asset_name, const std::string& directory_path)
{
  std::string target_directory_path = std::string();
  target_directory_path.append(directory_path);
  target_directory_path.append("/");
  target_directory_path.append(this->type_.GetName());
  target_directory_path.append("/");

  std::string target_asset_path = std::string();
  target_asset_path.append(asset_name);
  target_asset_path.append("/");
  target_asset_path.append(this->type_.GetName());
  target_asset_path.append("/");
  Crawl(this->type_, target_directory_path, target_asset_path, "", &this->asset_paths_);
}

void AssetData::CreateProgram(std::string* header, std::string* cpp)
{
  this->type_.CreateProgram(header, cpp, this->asset_paths_);
}

const std::string AssetData::ToString(T_UINT8 depth) const
{
  std::string ret = std::string();
  for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
  ret.append("TypeData {\n");

  ret.append(this->type_.ToString(depth + 1));

  for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
  ret.append("}\n");

  for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
  ret.append("Ids {\n");

  for (const auto& pair : this->asset_paths_)
  {
    for (T_UINT8 i = 0; i < depth + 1; ++i) ret.append("\t");
    ret.append("ID = ");
    ret.append(pair.first);
    ret.append(", Path = ");
    ret.append(pair.second);
    ret.append("\n");
  }

  for (T_UINT8 i = 0; i < depth; ++i) ret.append("\t");
  ret.append("}\n");
  return ret;
}
