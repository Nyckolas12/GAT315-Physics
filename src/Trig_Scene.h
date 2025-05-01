#pragma once
#include "scene.h"

class Trig_Scene : public Scene
{
public:
	Trig_Scene(const std::string& title, int width, int height, const Color& background = BLACK) : 
		Scene(title, width, height, background) {}




private:
	// Inherited via Scene
	void Initialize() override;

	void Update() override;

	void Draw() override;

	void DrawGUI() override;

};