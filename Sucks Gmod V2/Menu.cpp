#include "Menu.h"

void Menu::StyleInit()
{
	ImGui::StyleColorsDark();
}

void Menu::RenderMenu()
{
	ImGui::StyleColorsDark();
	static TextEditor textEditor;
	static bool initTextEditor = true;
	if (initTextEditor) { initTextEditor = false; textEditor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua()); };
	
	if (ImGui::Begin("Sucks Gmod v2", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		if (ImGui::BeginTabBar("##settings"))
		{
			if (ImGui::BeginTabItem("Esp"))
			{
				ImGui::Checkbox("Box Esp", &G::Variables::EspEnabled);
				ImGui::Checkbox("Tracers", &G::Variables::EspSnaplinesEnabled);

				ImGui::ColorPicker3("Box Color", G::Variables::boxColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorPicker3("Text Color", G::Variables::textColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Aimbot"))
			{
				ImGui::Checkbox("Aimbot", &G::Variables::AimbotEnabled);
				ImGui::Checkbox("Aimbot Smoothing", &G::Variables::AimbotSmoothingEnabled);
				ImGui::Checkbox("Silent Aimbot", &G::Variables::AimbotSilent);
				ImGui::DragInt("Aimbot FOV", &G::Variables::AimbotFOV, 1.0f, 0, 180);
				ImGui::DragInt("Aimbot Smoothing Amount", &G::Variables::AimbotSmoothing, 1.0f, 1, 100);
				
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Misc"))
			{
				ImGui::Checkbox("FPS Counter", &G::Variables::FpsMeter);
				ImGui::Checkbox("Simple Crosshair", &G::Variables::SimpleCrosshair);
				ImGui::Checkbox("Show Nearest Entity Info", &G::Variables::NearestEntInfo);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Lua Executor"))
			{
				textEditor.Render("Lua Executor", ImVec2(600, 400), false);

				if (ImGui::Button("Execute Lua"))
					gmodSDK->RunString(textEditor.GetText().c_str());

				ImGui::SameLine();

				if (ImGui::Button("Execute Lua (OLD)"))
					gmodSDK->RunLua(textEditor.GetText().c_str());

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
			
		ImGui::End();
	}
}
