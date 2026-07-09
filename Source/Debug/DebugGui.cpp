#include"DebugGui.hpp"
void PixelDome::DebugGui::Render(const PixelDome::Player& player)
{
	if (ImGui::IsKeyPressed(ImGuiKey_F1))
	{
		_pressedF1 = !_pressedF1;
	}
	if (_pressedF1)
	{
		ImGui::Begin("Debug");
		if (ImGui::BeginTabBar("DebugTab"))
		{
			if (ImGui::BeginTabItem("Player"))
			{
				ImGui::Text("Position:       %.2f, %.2f", player.GetPosition().x, player.GetPosition().y);
				ImGui::Text("PositionFmod:   %.2f, %.2f", std::fmod(player.GetPosition().x, 1.0f), std::fmod(player.GetPosition().y, 1.0f));
				ImGui::Text("Speed:          %.2f, %.2f", player.GetSpeed().x, player.GetSpeed().y);
				ImGui::Text("Size:           %.2f, %.2f", player.GetSize().x, player.GetSize().y);
				ImGui::Text("Acceleration:   %.2f", player.GetAcceleration());
				ImGui::Text("Drag:           %.2f", player.GetDrag());
				ImGui::Text("Width:          %.2f", player.GetWidth());
				ImGui::Text("Height:         %.2f", player.GetHeight());
				ImGui::Text("AnimationState: %zu", player.GetAnimationState());
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}