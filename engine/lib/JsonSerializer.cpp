#include "JsonSerializer.hh"

bool JsonSerializer::Serialize(IJsonSerializable* pObj, std::string& output)
{
	if (pObj == NULL)
		return false;

	Json::Value serializeRoot;
	pObj->Serialize(serializeRoot);

	Json::StyledWriter writer;
	output = writer.write(serializeRoot);

	return true;
}

bool JsonSerializer::Deserialize(IJsonSerializable* pObj, std::string& input)
{
	if (pObj == NULL)
		return false;

	Json::Value deserializeRoot;
	Json::Reader reader;

	if (!reader.parse(input, deserializeRoot, false))
		return false;

	pObj->Deserialize(deserializeRoot);

	return true;
}

bool JsonSerializer::DeserializeComponent(IJsonSerializable* pObj, std::string& input, std::string& component)
{
	if (pObj == NULL)
		return false;

	Json::Value deserializeRoot;
	Json::Reader reader;

	if (!reader.parse(input, deserializeRoot, false))
		return false;

	pObj->Deserialize(deserializeRoot[component]);

	return true;
}
