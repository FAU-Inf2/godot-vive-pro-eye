/*
 * This file is part of godot-vive-pro-eye, a Godot 3 driver for the HTC
 * Vive Pro Eye eye tracking hardware.
 *
 * Copyright (c) 2019 Lehrstuhl für Informatik 2,
 * Friedrich-Alexander-Universität Erlangen-Nürnberg (FAU)
 * Author: Florian Jung (florian.jung@fau.de)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include <string>

#include "myclass.h"

#include "SRanipal.h"
#include "SRanipal_Eye.h"
#include "SRanipal_Enums.h"

#include <boost/lockfree/spsc_queue.hpp>
#include <thread>
#include <chrono>


using namespace godot;
using namespace std;
using namespace ViveSR;

void MyClass::_register_methods() {
	#define reg(name) register_method(#name, &MyClass::name)
	reg(update_eye_data);
	reg(next_eye_data);
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
					poll_thread = std::thread(&MyClass::poll, this);
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

void MyClass::poll()
{
	ViveSR::anipal::Eye::EyeData poll_eye_data;

	while (true)
	{
		std::this_thread::sleep_for(1ms);

		int prev_frame = poll_eye_data.frame_sequence;
		int result = ViveSR::anipal::Eye::GetEyeData(&poll_eye_data);
		if (result == ViveSR::Error::WORK)
		{
			int delta = poll_eye_data.frame_sequence - prev_frame;

			if (delta > 0)
			{
				if (delta > 1)
					cout << "frame delta: " << poll_eye_data.frame_sequence - prev_frame << endl;

				bool success = queue.push(poll_eye_data);

				if (!success)
					cout << "ringbuf overflow" << endl;
			}
		}
	}
}

bool MyClass::next_eye_data()
{
	bool success = queue.pop(eye_data);
	if (success)
		data_valid = true;
	return success;
}

bool MyClass::update_eye_data()
{
	bool success = false;
	while (next_eye_data())
		success = true;
	return success;
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
	return eye_data.timestamp;
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
