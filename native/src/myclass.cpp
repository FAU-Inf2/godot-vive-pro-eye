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
	#define reg(name) register_method(#name, &MyClass::name)
	reg(update_eye_data);
	reg(get_eyeball_position);
	reg(get_gaze_direction);
	reg(is_user_present);
	reg(get_timestamp);
	reg(get_gaze_distance);
	reg(get_pupil_size);
	reg(get_eye_openness);
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

bool MyClass::update_eye_data()
{
	if (init_success)
	{
		int prev_frame = eye_data.frame_sequence;
		int result = ViveSR::anipal::Eye::GetEyeData(&eye_data);
		data_valid = (result == ViveSR::Error::WORK);

		cout << "frame delta: " << eye_data.frame_sequence - prev_frame << endl;
	}
	else
	{
		data_valid = false;
	}
	return data_valid;
}


const ViveSR::anipal::Eye::SingleEyeData* MyClass::get_eye(int eye)
{
	ViveSR::anipal::Eye::SingleEyeData* e;
	switch(eye)
	{
		case -1: e = &eye_data.verbose_data.left; break;
		case  1: e = &eye_data.verbose_data.right; break;
		default: e = &eye_data.verbose_data.combined.eye_data; break;
	}
	return e;
}

static godot::Vector3 convert_vec(const ViveSR::anipal::Eye::Vector3& v)
{
	return godot::Vector3(-v.x, v.y, -v.z);
}

Vector3 MyClass::get_eyeball_position(int eye)
{
	return convert_vec(get_eye(eye)->gaze_origin_mm) / 1000.0;
}

Vector3 MyClass::get_gaze_direction(int eye)
{
	return convert_vec(get_eye(eye)->gaze_direction_normalized);
}

bool MyClass::is_user_present()
{
	return eye_data.no_user;
}

double MyClass::get_timestamp()
{
	return eye_data.no_user;
}

double MyClass::get_gaze_distance()
{
	if (eye_data.verbose_data.combined.convergence_distance_validity)
		return eye_data.verbose_data.combined.convergence_distance_mm / 1000.;
	else
		return -1.;
}

double MyClass::get_pupil_size(int eye)
{
	return get_eye(eye)->pupil_diameter_mm;
}

double MyClass::get_eye_openness(int eye)
{
	return get_eye(eye)->eye_openness;
}
