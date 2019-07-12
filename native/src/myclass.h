#pragma once

#include <Godot.hpp>
#include <Spatial.hpp>
#include <Material.hpp>
#include <MeshInstance.hpp>

#include "SRanipal.h"
#include "SRanipal_Eye.h"

namespace godot {

class MyClass : public godot::Node {
	GODOT_CLASS(MyClass, godot::Node)

private:
	bool init_success = false;
	bool data_valid = false;

	ViveSR::anipal::Eye::EyeData eye_data;

public:
	static void _register_methods();
	
	void _process(float delta);
	void update_eye_data();

	MyClass();
	~MyClass();
	void _init();
};

}
