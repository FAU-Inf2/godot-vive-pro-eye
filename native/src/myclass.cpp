#include <iostream>
#include <string>
#include "myclass.h"

using namespace godot;
using namespace std;

void MyClass::_register_methods() {
	register_method("_process", &MyClass::_process);
	register_method("bark", &MyClass::bark);
	register_property("disco_material", &MyClass::disco_material, Ref<Material>(), GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, "Material");
	register_property("party_material", &MyClass::party_material, Ref<Material>(), GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, "Material");
	register_property("time_delta", &MyClass::time_delta, 0.5f, GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_NONE);
}

MyClass::MyClass() {
	cout << "MyClass ctor" << endl;
}

MyClass::~MyClass() {
	cout << "MyClass dtor" << endl;
}

std::string to_string(const godot::String& str)
{
	if (char* data = str.alloc_c_string())
	{
		std::string result(data);
		godot::api->godot_free(data);
		return result;
	}
	else
		throw runtime_error("Failed to alloc_c_string()");
}
void MyClass::bark(godot::String str)
{
	cout << "woof " << to_string(str) << "woof" << endl;
}

void MyClass::_process(float delta) {
	time_passed += delta;
	
	if (time_passed >= time_delta)
	{
		time_passed = 0;

		if (state/2 == 0)
		{
			cout << "disco" << endl;
			owner->set_material_override(disco_material);
		}
		else
		{
			cout << "party" << endl;
			owner->set_material_override(party_material);
		}

		state = (state+1) % 4;
	}
}
