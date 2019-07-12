#include <iostream>
#include <string>
#include "myclass.h"

#include "SRanipal.h"
#include "SRanipal_Eye.h"
#include "SRanipal_Enums.h"

using namespace godot;
using namespace std;
using namespace ViveSR;

void MyClass::_register_methods() {
	register_method("_process", &MyClass::_process);
}


void MyClass::_init()
{
	cout << "MyClass::_init()" << endl;

	if (ViveSR::anipal::Eye::IsViveProEye())
	{
			ViveSR::Error err = static_cast<ViveSR::Error>(ViveSR::anipal::Initial(ViveSR::anipal::Eye::ANIPAL_TYPE_EYE, NULL));
			switch (err)
			{
				case ViveSR::Error::WORK:
					cout << "Successfully initialized SRanipal." << endl;
					init_success = true;
					break;
				case ViveSR::Error::RUNTIME_NOT_FOUND:
					cout << "Failed to initialize SRanipal: Runtime not found." << endl;
					break;
				default:
					cout << "Failed to initialize SRanipal. Unknown error code " << err << endl;
			}
	}
	else
	{
		cout << "Error: HMD is not a Vive Pro Eye" << endl;
	}
}

MyClass::MyClass() {
	cout << "MyClass ctor" << endl;
}

MyClass::~MyClass() {
	cout << "MyClass dtor" << endl;
}

void MyClass::update_eye_data()
{
	if (init_success)
	{
		int result = ViveSR::anipal::Eye::GetEyeData(&eye_data);
		data_valid = (result == ViveSR::Error::WORK);
	}
	else
	{
		data_valid = false;
	}
}

void MyClass::_process(float delta) {
	update_eye_data();
	
	if (data_valid)
	{
		cout <<
			eye_data.verbose_data.combined.eye_data.gaze_direction_normalized.x << "," <<
			eye_data.verbose_data.combined.eye_data.gaze_direction_normalized.y << "," <<
			eye_data.verbose_data.combined.eye_data.gaze_direction_normalized.z << "  |  " <<
			eye_data.verbose_data.combined.eye_data.gaze_origin_mm.x << "," <<
			eye_data.verbose_data.combined.eye_data.gaze_origin_mm.y << "," <<
			eye_data.verbose_data.combined.eye_data.gaze_origin_mm.z << endl;
	}
}
