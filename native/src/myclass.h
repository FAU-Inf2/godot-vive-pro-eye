#pragma once

#include <Godot.hpp>
#include <Spatial.hpp>
#include <Material.hpp>
#include <MeshInstance.hpp>


namespace godot {

class MyClass : public godot::GodotScript<MeshInstance> {
	GODOT_CLASS(MyClass)

private:
	float time_passed = 0.f;
	Ref<Material> disco_material;
	Ref<Material> party_material;
	float time_delta = 0.5f;
	int state = 0;

public:
	static void _register_methods();

	MyClass();
	~MyClass();

	void _process(float delta);
	void bark(godot::String str);
};

}
