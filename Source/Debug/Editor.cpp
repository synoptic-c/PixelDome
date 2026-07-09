#include"Editor.hpp"
PixelDome::Editor::Editor(std::string_view path)
	: _chooseTile(0),
	_tempMouseX(0),
	_tempMouseY(0),
	_tempSelected(0),
	_tempSetLoadPositionX(0),
	_tempSetLoadPositionY(0),
	_tempSetMapPath(""),
	_tempChooseItem(0)

{
	_tempChooseIndex = std::nullopt;
	UpdateTemp(path);
}
void PixelDome::Editor::UpdateTemp(std::string_view path)
{
	nlohmann::json jsonLevel = PixelDome::LoadJson(path);
	_tempMapName = jsonLevel["mapName"].get<std::string>();
	_tempWidthCount = jsonLevel["widthCount"].get<size_t>();
	_tempHeightCount = jsonLevel["heightCount"].get<size_t>();
	_tempPlayerPositionX = jsonLevel["playerPosition"]["x"].get<float>();
	_tempPlayerPositionY = jsonLevel["playerPosition"]["y"].get<float>();
}
void PixelDome::Editor::Render(bool mouseLeft, bool mouseRight, const PixelDome::Player& player, PixelDome::Window& window, const PixelDome::Camera& camera, PixelDome::Level& level, const PixelDome::Tile& tile)
{
	if (ImGui::IsKeyPressed(ImGuiKey_F2))
	{
		_pressedF2 = !_pressedF2;
	}
	if (_pressedF2)
	{
		ImGui::Begin("LevelEditor");
		if (ImGui::BeginTabBar("Settings"))
		{
			if (ImGui::BeginTabItem("Basic"))
			{
				char temp[128];
				strcpy_s(temp, sizeof(temp), _tempMapName.c_str());
				if (ImGui::InputText("MapName", temp, sizeof(temp)))
				{
					_tempMapName = temp;
				}
				ImGui::InputScalar("WidthCount", ImGuiDataType_U64, &_tempWidthCount);
				ImGui::InputScalar("HeightCount", ImGuiDataType_U64, &_tempHeightCount);
				ImGui::InputScalar("PlayerPositionX", ImGuiDataType_Float, &_tempPlayerPositionX);
				ImGui::InputScalar("PlayerPositionY", ImGuiDataType_Float, &_tempPlayerPositionY);
				if (ImGui::Button("ResetLevel"))
				{
					level.SetLevel(_tempWidthCount, _tempHeightCount);
					level.SetMapIndices(_tempWidthCount, _tempHeightCount);
				}
				if (ImGui::Button("Save"))
				{
					PixelDome::JsonLoader jsonLoader;
					nlohmann::json jsonSave;
					jsonSave["mapName"] = _tempMapName;
					jsonSave["playerPosition"]["x"] = _tempPlayerPositionX;
					jsonSave["playerPosition"]["y"] = _tempPlayerPositionY;
					jsonSave["widthCount"] = level.GetWidthCount();
					jsonSave["heightCount"] = level.GetHeightCount();
					jsonSave["loadPositionXs"] = level.GetLoadPositionXs();
					jsonSave["loadPositionYs"] = level.GetLoadPositionYs();
					jsonSave["mapPaths"] = level.GetMapPaths();
					jsonSave["levelData"] = level.GetData();
					jsonSave["mapIndices"] = level.GetMapIndices();
					std::ofstream file(jsonLoader.GetJson()["mapSaveDefault"].get<std::string>() + _tempMapName + ".json");
					file << jsonSave.dump(4);
				}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("SetTile"))
			{
				if (mouseRight)
				{
					_tempMouseX = camera.GetView().x + window.GetFixMouseX(camera);
					_tempMouseY = camera.GetView().y + window.GetFixMouseY(camera);
					if (level.GetTile(_tempMouseX, _tempMouseY).has_value())
					{
						_tempChooseIndex = level.GetTile(_tempMouseX, _tempMouseY).value();
					}
				}
				if (_tempChooseIndex.has_value())
				{
					if (_tempMouseX >= 0 && _tempMouseY >= 0 && _tempMouseX < level.GetWidthCount() && _tempMouseY < level.GetHeightCount())
					{
						ImGui::Text("Position: %zu, %zu", _tempMouseX, _tempMouseY);
						ImGui::Image((ImTextureID)(intptr_t)tile.GetTextures()[level.GetTile(_tempMouseX, _tempMouseY).value()].GetTexture(), ImVec2(50.0f, 50.0f));
						int tempMapIndex = level.GetMapIndex(_tempMouseX, _tempMouseY);
						ImGui::InputScalar("MapIndex", ImGuiDataType_S32, &(tempMapIndex));
						level.SetMapIndex(_tempMouseX, _tempMouseY, tempMapIndex);
					}
				}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("SetLoadLevel"))
			{
				ImGui::InputText("SetMapPath", _tempSetMapPath, sizeof(_tempSetMapPath));
				ImGui::InputScalar("SetLoadPositionX", ImGuiDataType_Float, &_tempSetLoadPositionX);
				ImGui::InputScalar("SetLoadPositionY", ImGuiDataType_Float, &_tempSetLoadPositionY);
				if (ImGui::Button("AddItem"))
				{
					level.AddLoadPositionX(_tempSetLoadPositionX);
					level.AddLaodPositionY(_tempSetLoadPositionY);
					level.AddLoadMapPath(_tempSetMapPath);
				}
				ImGui::InputScalar("ChooseItem", ImGuiDataType_S32, &_tempChooseItem);
				if (ImGui::Button("RemoveChooseItem"))
				{
					level.RemoveLoadPositionX(_tempChooseItem);
					level.RemoveLoadPositionY(_tempChooseItem);
					level.RemoveLoadMapPath(_tempChooseItem);
				}
				if (ImGui::BeginCombo("LoadLevelData", level.GetMapPath(_tempSelected).c_str()))
				{
					for (size_t i = 0; i < level.GetMapPaths().size(); i++)
					{
						ImGui::PushID(i);
						if (ImGui::Selectable(level.GetMapPath(i).c_str(), _tempSelected == i))
						{
							_tempSelected = i;
						}
						ImGui::PopID();
					}
					ImGui::EndCombo();
				}
				char temp[128];
				strcpy_s(temp, sizeof(temp), level.GetMapPath(_tempSelected).c_str());
				if (ImGui::InputText("MapPath", temp, sizeof(temp)))
				{
					level.SetMapPath(_tempSelected, temp);
				}
				float tempLoadPositionX = level.GetLoadPositionX(_tempSelected);
				ImGui::InputScalar("loadPositionX", ImGuiDataType_Float, &tempLoadPositionX);
				level.SetLoadPositionX(_tempSelected, tempLoadPositionX);
				float tempLoadPositionY = level.GetLoadPositionY(_tempSelected);
				ImGui::InputScalar("loadPositionY", ImGuiDataType_Float, &tempLoadPositionY);
				level.SetLoadPositionY(_tempSelected, tempLoadPositionY);
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
		ImGui::Begin("TileMap");
		for (size_t i = 0; i < tile.GetTextures().size(); i++)
		{
			if (ImGui::ImageButton(tile.GetNames()[i].c_str(), (ImTextureID)(intptr_t)tile.GetTextures()[i].GetTexture(), ImVec2(50.0f, 50.0f)))
			{
				_chooseTile = i;
			}
			if (i % 2 == 0)
			{
				ImGui::SameLine();
			}
		}
		ImGui::End();
		if (!ImGui::GetIO().WantCaptureMouse)
		{
			if (mouseLeft)
			{
				float fixMouseX = camera.GetView().x + window.GetFixMouseX(camera);
				float fixMouseY = camera.GetView().y + window.GetFixMouseY(camera);
				level.SetTile((size_t)fixMouseX, (size_t)fixMouseY, _chooseTile);
			}
		}
	}
}